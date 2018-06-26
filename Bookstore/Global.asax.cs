using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using System.Web.Security;
using System.Web.SessionState;
using System.Web.Http;
using Bookstore.App_Start;
using System.Web.Optimization;
using System.Data.Entity;
using Bookstore.DataAccessLayer;
using System.Diagnostics;

namespace Bookstore
{
   public class Global : HttpApplication
   {
      void Application_Start(object sender, EventArgs e)
      {
         Database.SetInitializer(new BookstoreDBInitializer());

         // Code that runs on application startup
         AreaRegistration.RegisterAllAreas();
         RegisterRoutes(RouteTable.Routes);
         BundleConfig.RegisterBundles(BundleTable.Bundles);
      }

      public static void RegisterRoutes(RouteCollection routes)
      {
         routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

         routes.MapRoute(
             "Default",                                              // Route name 
             "{controller}/{action}/{id}",                           // URL with parameters 
             new { controller = "Dashboard", action = "Index", id = "" }  // Parameter defaults
         );

      }
   }
}