namespace Bookstore.Controllers
{
   using System.Collections.Generic;
   using System.Web.Mvc;
   using Bookstore.Models;

   public class HeaderController : Controller
   {
      public ActionResult Navigation()
      {
         var model = new List<NavigationModel>
         {
            new NavigationModel { Action = "Login", Controller = "User", Title = "Login" },
            new NavigationModel { Action = nameof(Index), Controller = "User", Title = "Register" },
            new NavigationModel { Action = nameof(Index), Controller = "Dashboard", Title = "Dashboard" },
            new NavigationModel { Action = nameof(Index), Controller = "Product", Title = "Product" }
         };

         return PartialView("_Navigation", model);
      }

      public ActionResult Index()
      {
         var model = nameof(Bookstore);

         return PartialView("_Index", model);
      }
   }
}