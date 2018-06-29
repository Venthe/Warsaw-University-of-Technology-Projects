namespace Bookstore.Models
{
   using System.ComponentModel.DataAnnotations;
   using System.ComponentModel.DataAnnotations.Schema;

   public class Session
   {
      [Required]
      [StringLength(450)]
      [Index("IX_UniqueHobbyCode", IsUnique = true)]
      public string Key { get; set; }

      [Key]
      [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
      public int SessionId { get; set; }

      public virtual User User { get; set; }
   }
}