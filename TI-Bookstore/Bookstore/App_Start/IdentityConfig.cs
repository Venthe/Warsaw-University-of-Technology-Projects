namespace Bookstore.App_Start
{
   using System.Data.Entity;
   using Bookstore.DataAccessLayer;
   using Bookstore.Models;
   using Bookstore.Service;
   using Microsoft.AspNet.Identity;
   using Microsoft.AspNet.Identity.EntityFramework;
   using Microsoft.Owin;
   using Microsoft.Owin.Security.Cookies;
   using Owin;

   public static class IdentityConfig
   {
      public static void Configuration(IAppBuilder app)
      {
         app.CreatePerOwinContext(() => new BookstoreDBContext());
         app.CreatePerOwinContext<AppUserManagerService>(AppUserManagerService.Create);
         app.CreatePerOwinContext(() => new RoleManager<AppRole>(new RoleStore<AppRole>()));

         app.UseCookieAuthentication(new CookieAuthenticationOptions
         {
            AuthenticationType = DefaultAuthenticationTypes.ApplicationCookie,
            LoginPath = new PathString("/Home/Login"),
         });
      }
   }
}