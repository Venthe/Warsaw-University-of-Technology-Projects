using Bookstore.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Data.Entity.ModelConfiguration.Conventions;
using System.Diagnostics;
using System.Linq;
using System.Web;

namespace Bookstore.DataAccessLayer
{
   public class BookstoreDBContext : DbContext
   {

      public BookstoreDBContext() : base("name=BookstoreDBContext")
      {
         Database.SetInitializer(new BookstoreDBInitializer());
      }

      public DbSet<Hobby> Hobby { get; set; }
      public DbSet<Education> Education { get; set; }
      public DbSet<User> Users { get; set; }
      public DbSet<Address> Addresses { get; set; }

      protected override void OnModelCreating(DbModelBuilder modelBuilder)
      {
         modelBuilder.Entity<User>()
          .HasRequired<Address>(s => s.Address)
          .WithMany(g => g.Users)
          .HasForeignKey<int>(s => s.AddressId);

         modelBuilder.Entity<User>()
              .HasMany<Hobby>(s => s.Hobbies)
              .WithMany(c => c.Users)
              .Map(cs =>
              {
                 cs.MapLeftKey("UserRefId");
                 cs.MapRightKey("HobbyRefId");
                 cs.ToTable("UserHobby");
              });

         modelBuilder.Entity<User>()
          .HasRequired<Education>(s => s.Education)
          .WithMany(g => g.Users)
          .HasForeignKey<int>(s => s.EducationId);

         base.OnModelCreating(modelBuilder);
      }
   }
}