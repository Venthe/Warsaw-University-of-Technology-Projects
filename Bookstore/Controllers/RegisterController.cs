using Bookstore.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Bookstore.Controllers
{
   public class RegisterController : Controller
   {
      public ActionResult Index()
      {
         return View();
      }

      [HttpPost]
      public ActionResult Index(UserModel userModel) {
         if (ModelState.IsValid)
         {
            return RedirectToAction("Index", "Dashboard");
         }

         return View();
      }
   }
}