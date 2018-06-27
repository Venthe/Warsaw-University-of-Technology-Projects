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
            new NavigationModel() { Action = "Index", Controller = "Login", Title = "Login" },
            new NavigationModel() { Action = "Index", Controller = "User", Title = "Register" },
            new NavigationModel() { Action = "Index", Controller = "Dashboard", Title = "Dashboard" },
            new NavigationModel() { Action = "Index", Controller = "Product", Title = "Product" }
         };

         return PartialView("_Navigation", model);
      }

      public ActionResult Index()
      {
         var model = "Bookstore";

         return PartialView("_Index", model);
      }
   }
}