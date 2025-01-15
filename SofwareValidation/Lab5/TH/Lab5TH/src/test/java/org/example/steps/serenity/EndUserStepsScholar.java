package org.example.steps.serenity;

import net.thucydides.core.annotations.Step;
import org.example.pages.ScholarPage;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.containsString;
import static org.hamcrest.Matchers.hasItem;

public class EndUserStepsScholar {
    ScholarPage scholarPage;

    @Step
    public void enters(String keyword) {
        scholarPage.enter_keywords(keyword);
    }

    @Step
    public void starts_search() {
        scholarPage.lookup_terms();
    }

    @Step
    public void filters(String start){
        scholarPage.enter_start_and_end_year(start);
    }

    @Step
    public void start_filter(){
        scholarPage.filter_range();
    }

    @Step
    public void do_filter(){
        scholarPage.do_filter();
    }

    @Step
    public void should_see_title(String title) {
        assertThat(scholarPage.getTitles(), hasItem(containsString(title)));
    }

    @Step
    public void is_the_home_page() {
        scholarPage.open();
    }

    @Step
    public void looks_for(String term, String start) {
        enters(term);
        starts_search();
        start_filter();
        filters(start);
        do_filter();
    }
}
