namespace Bookstore.Controllers
{
   using System.Web.Mvc;
   using Bookstore.Models;

   public class LoginController : Controller
   {
      public ActionResult Index()
      {
         return View();
      }

      [HttpPost]
      public ActionResult Index(UserLogin userLogin)
      {
         if (ModelState.IsValid)
         {
            return RedirectToAction("Index", "Dashboard");
         }

         return View();
      }
   }
}
