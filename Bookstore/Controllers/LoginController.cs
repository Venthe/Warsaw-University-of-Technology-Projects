using Bookstore.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Bookstore.Controllers
{
   public class LoginController : Controller
   {
      // GET: Login
      public ActionResult Index()
      {
         return View();
      }

      // POST: Login
      [HttpPost]
      public ActionResult Index(FormCollection collection)
      {
         try
         {
            // TODO: Add insert logic here
            var userModel = new UserModel()
            {
               Username = collection.Get(0)
            };

            return RedirectToAction("Index", "Dashboard");
         }
         catch
         {
            return View();
         }
      }
   }
}
