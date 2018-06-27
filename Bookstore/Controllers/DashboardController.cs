namespace Bookstore.Controllers
{
   using System.Web.Mvc;
   using Bookstore.Models;

   public class DashboardController : Controller
   {
      public ActionResult Index()
      {
         var user = new User();

         return View(user);
      }
   }
}