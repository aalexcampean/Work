using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace AcademicInfoAPI.Data.Migrations
{
    public partial class v4 : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_ContractOfStudy_AspNetUsers_UserID",
                table: "ContractOfStudy");

            migrationBuilder.DropForeignKey(
                name: "FK_Courses_Curriculum_CurriculumID",
                table: "Courses");

            migrationBuilder.DropForeignKey(
                name: "FK_Curriculum_YearOfStudy_Year",
                table: "Curriculum");

            migrationBuilder.DropForeignKey(
                name: "FK_CurriculumContract_ContractOfStudy_CurriculumID",
                table: "CurriculumContract");

            migrationBuilder.DropForeignKey(
                name: "FK_CurriculumContract_Curriculum_CurriculumID",
                table: "CurriculumContract");

            migrationBuilder.DropPrimaryKey(
                name: "PK_YearOfStudy",
                table: "YearOfStudy");

            migrationBuilder.DropPrimaryKey(
                name: "PK_CurriculumContract",
                table: "CurriculumContract");

            migrationBuilder.DropPrimaryKey(
                name: "PK_Curriculum",
                table: "Curriculum");

            migrationBuilder.DropPrimaryKey(
                name: "PK_ContractOfStudy",
                table: "ContractOfStudy");

            migrationBuilder.RenameTable(
                name: "YearOfStudy",
                newName: "YearsOfStudies");

            migrationBuilder.RenameTable(
                name: "CurriculumContract",
                newName: "CurriculumContracts");

            migrationBuilder.RenameTable(
                name: "Curriculum",
                newName: "Curriculums");

            migrationBuilder.RenameTable(
                name: "ContractOfStudy",
                newName: "ContractsOfStudies");

            migrationBuilder.RenameIndex(
                name: "IX_Curriculum_Year",
                table: "Curriculums",
                newName: "IX_Curriculums_Year");

            migrationBuilder.RenameIndex(
                name: "IX_ContractOfStudy_UserID",
                table: "ContractsOfStudies",
                newName: "IX_ContractsOfStudies_UserID");

            migrationBuilder.AddPrimaryKey(
                name: "PK_YearsOfStudies",
                table: "YearsOfStudies",
                column: "Year");

            migrationBuilder.AddPrimaryKey(
                name: "PK_CurriculumContracts",
                table: "CurriculumContracts",
                columns: new[] { "CurriculumID", "ContractID" });

            migrationBuilder.AddPrimaryKey(
                name: "PK_Curriculums",
                table: "Curriculums",
                column: "ID");

            migrationBuilder.AddPrimaryKey(
                name: "PK_ContractsOfStudies",
                table: "ContractsOfStudies",
                column: "ID");

            migrationBuilder.AddForeignKey(
                name: "FK_ContractsOfStudies_AspNetUsers_UserID",
                table: "ContractsOfStudies",
                column: "UserID",
                principalTable: "AspNetUsers",
                principalColumn: "Id");

            migrationBuilder.AddForeignKey(
                name: "FK_Courses_Curriculums_CurriculumID",
                table: "Courses",
                column: "CurriculumID",
                principalTable: "Curriculums",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_CurriculumContracts_ContractsOfStudies_CurriculumID",
                table: "CurriculumContracts",
                column: "CurriculumID",
                principalTable: "ContractsOfStudies",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_CurriculumContracts_Curriculums_CurriculumID",
                table: "CurriculumContracts",
                column: "CurriculumID",
                principalTable: "Curriculums",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_Curriculums_YearsOfStudies_Year",
                table: "Curriculums",
                column: "Year",
                principalTable: "YearsOfStudies",
                principalColumn: "Year",
                onDelete: ReferentialAction.Cascade);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_ContractsOfStudies_AspNetUsers_UserID",
                table: "ContractsOfStudies");

            migrationBuilder.DropForeignKey(
                name: "FK_Courses_Curriculums_CurriculumID",
                table: "Courses");

            migrationBuilder.DropForeignKey(
                name: "FK_CurriculumContracts_ContractsOfStudies_CurriculumID",
                table: "CurriculumContracts");

            migrationBuilder.DropForeignKey(
                name: "FK_CurriculumContracts_Curriculums_CurriculumID",
                table: "CurriculumContracts");

            migrationBuilder.DropForeignKey(
                name: "FK_Curriculums_YearsOfStudies_Year",
                table: "Curriculums");

            migrationBuilder.DropPrimaryKey(
                name: "PK_YearsOfStudies",
                table: "YearsOfStudies");

            migrationBuilder.DropPrimaryKey(
                name: "PK_Curriculums",
                table: "Curriculums");

            migrationBuilder.DropPrimaryKey(
                name: "PK_CurriculumContracts",
                table: "CurriculumContracts");

            migrationBuilder.DropPrimaryKey(
                name: "PK_ContractsOfStudies",
                table: "ContractsOfStudies");

            migrationBuilder.RenameTable(
                name: "YearsOfStudies",
                newName: "YearOfStudy");

            migrationBuilder.RenameTable(
                name: "Curriculums",
                newName: "Curriculum");

            migrationBuilder.RenameTable(
                name: "CurriculumContracts",
                newName: "CurriculumContract");

            migrationBuilder.RenameTable(
                name: "ContractsOfStudies",
                newName: "ContractOfStudy");

            migrationBuilder.RenameIndex(
                name: "IX_Curriculums_Year",
                table: "Curriculum",
                newName: "IX_Curriculum_Year");

            migrationBuilder.RenameIndex(
                name: "IX_ContractsOfStudies_UserID",
                table: "ContractOfStudy",
                newName: "IX_ContractOfStudy_UserID");

            migrationBuilder.AddPrimaryKey(
                name: "PK_YearOfStudy",
                table: "YearOfStudy",
                column: "Year");

            migrationBuilder.AddPrimaryKey(
                name: "PK_Curriculum",
                table: "Curriculum",
                column: "ID");

            migrationBuilder.AddPrimaryKey(
                name: "PK_CurriculumContract",
                table: "CurriculumContract",
                columns: new[] { "CurriculumID", "ContractID" });

            migrationBuilder.AddPrimaryKey(
                name: "PK_ContractOfStudy",
                table: "ContractOfStudy",
                column: "ID");

            migrationBuilder.AddForeignKey(
                name: "FK_ContractOfStudy_AspNetUsers_UserID",
                table: "ContractOfStudy",
                column: "UserID",
                principalTable: "AspNetUsers",
                principalColumn: "Id");

            migrationBuilder.AddForeignKey(
                name: "FK_Courses_Curriculum_CurriculumID",
                table: "Courses",
                column: "CurriculumID",
                principalTable: "Curriculum",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_Curriculum_YearOfStudy_Year",
                table: "Curriculum",
                column: "Year",
                principalTable: "YearOfStudy",
                principalColumn: "Year",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_CurriculumContract_ContractOfStudy_CurriculumID",
                table: "CurriculumContract",
                column: "CurriculumID",
                principalTable: "ContractOfStudy",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_CurriculumContract_Curriculum_CurriculumID",
                table: "CurriculumContract",
                column: "CurriculumID",
                principalTable: "Curriculum",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
