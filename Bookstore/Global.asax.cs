namespace Bookstore
{
   using System;
   using System.Data.Entity;
   using System.Web;
   using System.Web.Http;
   using System.Web.Mvc;
   using System.Web.Optimization;
   using System.Web.Routing;
   using Bookstore.App_Start;
   using Bookstore.DataAccessLayer;

   public class Global : HttpApplication
   {
      public static void RegisterRoutes(RouteCollection routes)
      {
         routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

         routes.MapRoute(
             "Default",                                              // Route name
             "{controller}/{action}/{id}",                           // URL with parameters
             new { controller = "Dashboard", action = "Index", id = string.Empty }) // Parameter defaults
         ;
      }

      public void Application_Start(object sender, EventArgs e)
      {
         // Code that runs on application startup
         AreaRegistration.RegisterAllAreas();
         RegisterRoutes(RouteTable.Routes);
         BundleConfig.RegisterBundles(BundleTable.Bundles);
      }
   }
}