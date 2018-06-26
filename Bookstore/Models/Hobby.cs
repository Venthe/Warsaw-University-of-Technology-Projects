using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Bookstore.Models
{
   public class Hobby
   {
      [Key, DatabaseGenerated(DatabaseGeneratedOption.Identity)]
      public int HobbyId { get; set; }

      [Required, StringLength(450), Index("IX_UniqueHobbyCode", IsUnique = true)]
      public string Code { get; set; }

      public ICollection<User> Users { get; set; } = new HashSet<User>();
   }
}