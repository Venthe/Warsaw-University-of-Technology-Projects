namespace Bookstore.Controllers
{
   using System.Collections.Generic;
   using System.Linq;
   using System.Web.Mvc;
   using Bookstore.DataAccessLayer;
   using Bookstore.Models;

   public class UserController : Controller
   {
      private readonly BookstoreDBContext dbContext;

      public UserController() => dbContext = new BookstoreDBContext();

      public ActionResult Create()
      {
         var userViewModel = new UserViewModel()
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

            return RedirectToAction("Success");
         }

         var model = new UserViewModel()
         {
            User = user,
            Hobby = PrepareHobbies(),
            Education = PrepareEducationItems()
         };

         return View(model);
      }

      public ActionResult List() => View(dbContext.Users.ToList());

      public ActionResult Success() => View();

      public ActionResult Index()
      {
         return View();
      }

      private ICollection<Education> PrepareEducationItems() => (from education in dbContext.Education select education).ToList();

      private ICollection<Hobby> PrepareHobbies() => (from hobby in dbContext.Hobby select hobby).ToList();

      private void UpdateHobbies(User user, FormCollection form)
      {
         string userHobbies = form.Get("User.Hobbies");
         if (userHobbies != null)
         {
            List<string> hobbyCodes = userHobbies.Split(',').ToList();
            if (hobbyCodes.Count != 0)
            {
               user.Hobbies = dbContext.Hobby.Where(hobby => hobbyCodes.Contains(hobby.Code)).ToList<Hobby>();
               ModelState["User.Hobbies"].Errors.Clear();
            }
         }
      }

      private void UpdateEducation(User user, FormCollection form)
      {
         var educationCode = form.Get("User.Education");
         if (educationCode != null)
         {
            user.Education = (from e in dbContext.Education where e.Code.Equals(educationCode) select e).First() as Education;
            ModelState["User.Education"].Errors.Clear();
         }
      }
   }
}