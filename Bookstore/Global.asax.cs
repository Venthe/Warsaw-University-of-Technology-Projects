namespace Bookstore
{
   using System;
   using System.Web;
   using System.Web.Mvc;
   using System.Web.Optimization;
   using System.Web.Routing;
   using Bookstore.App_Start;

   public class Global : HttpApplication
   {
      public void Application_Start(object sender, EventArgs e)
      {
         // Code that runs on application startup
         AreaRegistration.RegisterAllAreas();
         RouteConfig.RegisterRoutes(RouteTable.Routes);
         BundleConfig.RegisterBundles(BundleTable.Bundles);
      }
   }
}