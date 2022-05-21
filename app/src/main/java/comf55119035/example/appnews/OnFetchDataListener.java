package comf55119035.example.appnews;

import java.util.List;

import comf55119035.example.appnews.Models.NewsHeadlines;

public interface OnFetchDataListener<NewsApiResponse> {
    void onFetchData(List<NewsHeadlines> list, String message);
    void onError(String message);
}
