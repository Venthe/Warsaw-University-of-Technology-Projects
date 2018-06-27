namespace Bookstore.Controllers
{
   using System.Web.Mvc;
   using Bookstore.Models;

   public class LoginController : Controller
   {
      public ActionResult Index() => View();

      // UserLogin parameter is used to validate model
#pragma warning disable CC0057 // Unused parameters
      [HttpPost]
      public ActionResult Index(UserLogin userLogin)
#pragma warning restore CC0057 // Unused parameters
      {
         if (ModelState.IsValid)
         {
            return RedirectToAction(nameof(Index), "Dashboard");
         }

         return View();
      }
   }
}
