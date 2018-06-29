namespace Bookstore.Controllers
{
   using System;
   using System.Collections.Generic;
   using System.Linq;
   using System.Web.Mvc;
   using Bookstore.DataAccessLayer;
   using Bookstore.Models;
   using Bookstore.Services;

   public class UserController : Controller
   {
      private readonly AuthorizationService authorizationService;
      private readonly BookstoreDBContext dbContext;

      public UserController()
      {
         dbContext = new BookstoreDBContext();
         authorizationService = new AuthorizationService();
      }

      public ActionResult Create()
      {
         var userViewModel = new UserViewModel
         {
            Hobby = PrepareHobbies(),
            Education = PrepareEducationItems()
         };

         return View(userViewModel);
      }

      [HttpPost]
      public ActionResult Create(User user, FormCollection form)
      {
         UpdateHobbies(user, form);
         UpdateEducation(user, form);

         if (ModelState.IsValid)
         {
            // Save in DB
            dbContext.Users.Add(user);
            dbContext.SaveChanges();

            return RedirectToAction(nameof(Success));
         }

         var model = new UserViewModel
         {
            User = user,
            Hobby = PrepareHobbies(),
            Education = PrepareEducationItems()
         };

         return View(model);
      }

      public ActionResult Denied() => View();

      public ActionResult Index() => View();

      public ActionResult List()
      {
         if (authorizationService.IsAdmin(Request))
         {
            return View(dbContext.Users.ToList());
         }

         return RedirectToAction(nameof(Denied));
      }

      public ActionResult Login()
      {
         if (authorizationService.IsLoggedIn(Request))
         {
            return RedirectToAction(nameof(List));
         }

         return View();
      }

      [HttpPost]
      public ActionResult Login(LoginViewModel model)
      {
         if (!ModelState.IsValid)
         {
            return View(model);
         }

         var user = (from u in dbContext.Users where u.Username.Equals(model.Username, StringComparison.OrdinalIgnoreCase) && u.Password.Equals(model.Password) select u).Single();

         if (user == null)
         {
            // unauthorized
            return View(model);
         }

         var sessionHash = Guid.NewGuid().ToString();

         dbContext.Session.Add(new Session() { Key = sessionHash, User = user });
         dbContext.SaveChanges();

         Response.Cookies["BookstoreSession"]["SessionKey"] = sessionHash;
         Response.Cookies["BookstoreSession"].Expires = DateTime.Now.AddHours(1);

         return RedirectToAction(nameof(List));
      }

      public ActionResult Logout()
      {
         Response.Cookies["BookstoreSession"]["SessionKey"] = null;

         return RedirectToAction(nameof(Login));
      }

      public ActionResult Success() => View();

      private ICollection<Education> PrepareEducationItems() => (from education in dbContext.Education select education).ToList();

      private ICollection<Hobby> PrepareHobbies() => (from hobby in dbContext.Hobby select hobby).ToList();

      private void UpdateEducation(User user, FormCollection form)
      {
         var educationCode = form.Get("User.Education");
         if (educationCode != null)
         {
            user.Education = (from e in dbContext.Education where e.Code.Equals(educationCode) select e).First() as Education;
            ModelState["User.Education"].Errors.Clear();
         }
      }

      private void UpdateHobbies(User user, FormCollection form)
      {
         var userHobbies = form.Get("User.Hobbies");
         if (userHobbies != null)
         {
            var hobbyCodes = userHobbies.Split(',').ToList();
            if (hobbyCodes.Count != 0)
            {
               user.Hobbies = dbContext.Hobby.Where(hobby => hobbyCodes.Contains(hobby.Code)).ToList<Hobby>();
               ModelState["User.Hobbies"].Errors.Clear();
            }
         }
      }
   }
}