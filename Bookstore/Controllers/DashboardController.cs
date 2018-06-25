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
      // GET: Dashboard
      public ActionResult Index()
      {
         var userModel = new UserModel();

         return View(userModel);
      }
   }
}