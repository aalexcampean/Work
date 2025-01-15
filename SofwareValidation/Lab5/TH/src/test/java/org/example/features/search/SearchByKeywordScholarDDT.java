package org.example.features.search;

import net.serenitybdd.junit.runners.SerenityParameterizedRunner;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import net.thucydides.junit.annotations.Qualifier;
import net.thucydides.junit.annotations.UseTestDataFrom;
import org.example.steps.serenity.EndUserStepsScholar;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;

@RunWith(SerenityParameterizedRunner.class)
@UseTestDataFrom("src/test/resources/Scholar.csv")
public class SearchByKeywordScholarDDT {
    @Managed(uniqueSession = true)
    public WebDriver webdriver;

    @Steps
    public EndUserStepsScholar anna;

    public String keyword;
    public String title;
    public String start;

    @Qualifier
    public String getQualifier(){
        return keyword;
    }

    @Test
    public void searching_scholar_by_keyword_test_DDT() {
        anna.is_the_home_page();
        anna.looks_for(getKeyword(),getStart());
        anna.should_see_title(getTitle());
    }

    public String getKeyword(){
        return keyword;
    }

    public String getTitle(){
        return title;
    }

    public void setKeyword(String keyword){
        this.keyword = keyword;
    }

    public void setTitle(String title){
        this.title = title;
    }

    public String getStart() {
        return start;
    }

    public void setStart(String start) {
        this.start = start;
    }
}
