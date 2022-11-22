using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace AcademicInfoAPI.Data.Migrations
{
    public partial class v2 : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropIndex(
                name: "IX_ContractOfStudy_UserID",
                table: "ContractOfStudy");

            migrationBuilder.CreateIndex(
                name: "IX_ContractOfStudy_UserID",
                table: "ContractOfStudy",
                column: "UserID");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropIndex(
                name: "IX_ContractOfStudy_UserID",
                table: "ContractOfStudy");

            migrationBuilder.CreateIndex(
                name: "IX_ContractOfStudy_UserID",
                table: "ContractOfStudy",
                column: "UserID",
                unique: true,
                filter: "[UserID] IS NOT NULL");
        }
    }
}
