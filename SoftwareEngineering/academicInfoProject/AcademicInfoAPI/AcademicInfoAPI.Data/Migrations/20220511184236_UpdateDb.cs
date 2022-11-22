using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace AcademicInfoAPI.Data.Migrations
{
    public partial class UpdateDb : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Curriculums_YearsOfStudies_Year",
                table: "Curriculums");

            migrationBuilder.DropForeignKey(
                name: "FK_UserCourses_AspNetUsers_UserID",
                table: "UserCourses");

            migrationBuilder.DropTable(
                name: "CurriculumContracts");

            migrationBuilder.DropTable(
                name: "YearsOfStudies");

            migrationBuilder.DropPrimaryKey(
                name: "PK_UserCourses",
                table: "UserCourses");

            migrationBuilder.DropIndex(
                name: "IX_UserCourses_UserID",
                table: "UserCourses");

            migrationBuilder.DropIndex(
                name: "IX_Curriculums_Year",
                table: "Curriculums");

            migrationBuilder.DropIndex(
                name: "IX_ContractsOfStudies_UserID",
                table: "ContractsOfStudies");

            migrationBuilder.DropColumn(
                name: "UserID",
                table: "UserCourses");

            migrationBuilder.DropColumn(
                name: "ContractOfStudyID",
                table: "AspNetUsers");

            migrationBuilder.RenameColumn(
                name: "isOptional",
                table: "Courses",
                newName: "IsOptional");

            migrationBuilder.RenameColumn(
                name: "Id",
                table: "Courses",
                newName: "ID");

            migrationBuilder.AddColumn<int>(
                name: "ContractID",
                table: "UserCourses",
                type: "int",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.AddColumn<int>(
                name: "YearID",
                table: "ContractsOfStudies",
                type: "int",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.AddPrimaryKey(
                name: "PK_UserCourses",
                table: "UserCourses",
                columns: new[] { "CourseID", "ContractID" });

            migrationBuilder.CreateTable(
                name: "AcademicYear",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Year = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_AcademicYear", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Group",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    YearID = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Group", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Group_AcademicYear_YearID",
                        column: x => x.YearID,
                        principalTable: "AcademicYear",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "Student",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    UserID = table.Column<string>(type: "nvarchar(450)", nullable: true),
                    GroupID = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Student", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Student_AspNetUsers_UserID",
                        column: x => x.UserID,
                        principalTable: "AspNetUsers",
                        principalColumn: "Id");
                    table.ForeignKey(
                        name: "FK_Student_Group_GroupID",
                        column: x => x.GroupID,
                        principalTable: "Group",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_UserCourses_ContractID",
                table: "UserCourses",
                column: "ContractID");

            migrationBuilder.CreateIndex(
                name: "IX_ContractsOfStudies_UserID",
                table: "ContractsOfStudies",
                column: "UserID");

            migrationBuilder.CreateIndex(
                name: "IX_ContractsOfStudies_YearID",
                table: "ContractsOfStudies",
                column: "YearID");

            migrationBuilder.CreateIndex(
                name: "IX_Group_YearID",
                table: "Group",
                column: "YearID");

            migrationBuilder.CreateIndex(
                name: "IX_Student_GroupID",
                table: "Student",
                column: "GroupID");

            migrationBuilder.CreateIndex(
                name: "IX_Student_UserID",
                table: "Student",
                column: "UserID");

            migrationBuilder.AddForeignKey(
                name: "FK_ContractsOfStudies_AcademicYear_YearID",
                table: "ContractsOfStudies",
                column: "YearID",
                principalTable: "AcademicYear",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_UserCourses_ContractsOfStudies_ContractID",
                table: "UserCourses",
                column: "ContractID",
                principalTable: "ContractsOfStudies",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_ContractsOfStudies_AcademicYear_YearID",
                table: "ContractsOfStudies");

            migrationBuilder.DropForeignKey(
                name: "FK_UserCourses_ContractsOfStudies_ContractID",
                table: "UserCourses");

            migrationBuilder.DropTable(
                name: "Student");

            migrationBuilder.DropTable(
                name: "Group");

            migrationBuilder.DropTable(
                name: "AcademicYear");

            migrationBuilder.DropPrimaryKey(
                name: "PK_UserCourses",
                table: "UserCourses");

            migrationBuilder.DropIndex(
                name: "IX_UserCourses_ContractID",
                table: "UserCourses");

            migrationBuilder.DropIndex(
                name: "IX_ContractsOfStudies_UserID",
                table: "ContractsOfStudies");

            migrationBuilder.DropIndex(
                name: "IX_ContractsOfStudies_YearID",
                table: "ContractsOfStudies");

            migrationBuilder.DropColumn(
                name: "ContractID",
                table: "UserCourses");

            migrationBuilder.DropColumn(
                name: "YearID",
                table: "ContractsOfStudies");

            migrationBuilder.RenameColumn(
                name: "IsOptional",
                table: "Courses",
                newName: "isOptional");

            migrationBuilder.RenameColumn(
                name: "ID",
                table: "Courses",
                newName: "Id");

            migrationBuilder.AddColumn<string>(
                name: "UserID",
                table: "UserCourses",
                type: "nvarchar(450)",
                nullable: false,
                defaultValue: "");

            migrationBuilder.AddColumn<int>(
                name: "ContractOfStudyID",
                table: "AspNetUsers",
                type: "int",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.AddPrimaryKey(
                name: "PK_UserCourses",
                table: "UserCourses",
                columns: new[] { "CourseID", "UserID" });

            migrationBuilder.CreateTable(
                name: "CurriculumContracts",
                columns: table => new
                {
                    CurriculumID = table.Column<int>(type: "int", nullable: false),
                    ContractID = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_CurriculumContracts", x => new { x.CurriculumID, x.ContractID });
                    table.ForeignKey(
                        name: "FK_CurriculumContracts_ContractsOfStudies_ContractID",
                        column: x => x.ContractID,
                        principalTable: "ContractsOfStudies",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_CurriculumContracts_Curriculums_CurriculumID",
                        column: x => x.CurriculumID,
                        principalTable: "Curriculums",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "YearsOfStudies",
                columns: table => new
                {
                    Year = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    CurriculumID = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_YearsOfStudies", x => x.Year);
                });

            migrationBuilder.CreateIndex(
                name: "IX_UserCourses_UserID",
                table: "UserCourses",
                column: "UserID");

            migrationBuilder.CreateIndex(
                name: "IX_Curriculums_Year",
                table: "Curriculums",
                column: "Year",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_ContractsOfStudies_UserID",
                table: "ContractsOfStudies",
                column: "UserID",
                unique: true,
                filter: "[UserID] IS NOT NULL");

            migrationBuilder.CreateIndex(
                name: "IX_CurriculumContracts_ContractID",
                table: "CurriculumContracts",
                column: "ContractID");

            migrationBuilder.AddForeignKey(
                name: "FK_Curriculums_YearsOfStudies_Year",
                table: "Curriculums",
                column: "Year",
                principalTable: "YearsOfStudies",
                principalColumn: "Year",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_UserCourses_AspNetUsers_UserID",
                table: "UserCourses",
                column: "UserID",
                principalTable: "AspNetUsers",
                principalColumn: "Id",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
