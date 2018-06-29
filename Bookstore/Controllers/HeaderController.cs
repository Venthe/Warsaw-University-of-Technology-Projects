namespace Bookstore.Controllers
{
   using System.Collections.Generic;
   using System.Web.Mvc;
   using Bookstore.Models;
   using Bookstore.Services;

   public class HeaderController : Controller
   {
      private readonly AuthorizationService authorizationService;

      public HeaderController() => authorizationService = new AuthorizationService();

      public ActionResult Index()
      {
         var model = nameof(Bookstore);

         return PartialView("_Index", model);
      }

      public ActionResult Navigation()
      {
         var model = new List<NavigationModel>
         {
            new NavigationModel { Action = nameof(Index), Controller = "User", Title = "User action index" },
            new NavigationModel { Action = "Login", Controller = "User", Title = "Login" },
            new NavigationModel { Action = "Logout", Controller = "User", Title = "Logout" }
         };

         return PartialView("_Navigation", model);
      }

      public ActionResult UserDetails()
      {
         var model = new HeaderUserModelView { Username = authorizationService.GetCurrentUser(Request)?.Username, IsAdmin = authorizationService.IsAdmin(Request) };

         return PartialView("_UserDetails", model);
      }

   }
}