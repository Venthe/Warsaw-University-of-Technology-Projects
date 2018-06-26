namespace Bookstore.Migrations
{
   using System;
   using System.Data.Entity;
   using System.Data.Entity.Migrations;
   using System.Linq;

   internal sealed class Configuration : DbMigrationsConfiguration<Bookstore.Models.UserContext>
   {
      public Configuration()
      {
         AutomaticMigrationsEnabled = true;
         AutomaticMigrationDataLossAllowed = true;
         ContextKey = "Bookstore.Models.UserContext";
      }

      protected override void Seed(Bookstore.Models.UserContext context)
      {
         //  This method will be called after migrating to the latest version.

         //  You can use the DbSet<T>.AddOrUpdate() helper extension method 
         //  to avoid creating duplicate seed data.
      }
   }
}
