using Bookstore.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Bookstore.Controllers
{
   public class DashboardController : Controller
   {
      public ActionResult Index()
      {
         var user = new User();

         return View(user);
      }
   }
}