namespace Bookstore.Service
{
   using Bookstore.DataAccessLayer;
   using Bookstore.Models;
   using Microsoft.AspNet.Identity;
   using Microsoft.AspNet.Identity.EntityFramework;
   using Microsoft.AspNet.Identity.Owin;
   using Microsoft.Owin;

   public class AppUserManagerService : UserManager<AppUser>
   {
      // this method is called by Owin therefore best place to configure your User Manager
      public static AppUserManagerService Create(IdentityFactoryOptions<AppUserManagerService> options, IOwinContext context)
      {
         var manager = new AppUserManagerService(
             new UserStore<AppUser>(context.Get<BookstoreDBContext>()));

         // optionally configure your manager
         return manager;
      }

      public AppUserManagerService(IUserStore<AppUser> store)
          : base(store)
      {
      }
   }
}