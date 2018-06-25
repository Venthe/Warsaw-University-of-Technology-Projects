using Bookstore.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Bookstore.Controllers
{
   public class HeaderController : Controller
   {
      public ActionResult Navigation()
      {
         var model = new List<NavigationModel>
         {
            new NavigationModel() { Action = "Index", Controller = "Login", Title = "Login" },
            new NavigationModel() { Action = "Index", Controller = "Register", Title = "Register" },
            new NavigationModel() { Action = "Index", Controller = "Dashboard", Title = "Dashboard" }
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