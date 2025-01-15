package org.example.pages;

import net.serenitybdd.core.annotations.findby.FindBy;
import net.serenitybdd.core.pages.PageObject;
import net.serenitybdd.core.pages.WebElementFacade;
import net.thucydides.core.annotations.DefaultUrl;
import org.openqa.selenium.By;

import java.util.List;
import java.util.stream.Collectors;

@DefaultUrl("https://scholar.google.com/")
public class ScholarPage extends PageObject {

    @FindBy(name = "q")
    private WebElementFacade searchTerms;

    @FindBy(name="btnG")
    private WebElementFacade lookupButton;

    @FindBy(id ="gs_res_sb_yyc")
    private WebElementFacade customRange;

    public void enter_keywords(String keyword) {
        searchTerms.type(keyword);
    }

    public void lookup_terms() {
        lookupButton.click();
    }

    public void filter_range() {
        customRange.click();
    }

    public void do_filter(){
        find(By.xpath("/html/body/div/div[10]/div[1]/div/div[1]/form/div[2]/button")).click();
    }

    public void enter_start_and_end_year(String start){
        find(By.id("gs_as_ylo")).type(start);
    }

    public List<String> getTitles(){
        return findAll(By.tagName("a")).stream().map(WebElementFacade::getText).collect(Collectors.toList());
    }
}
