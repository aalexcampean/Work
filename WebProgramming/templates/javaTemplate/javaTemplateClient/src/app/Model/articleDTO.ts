export interface ArticleDTO {
  id: number,
  userName: string,
  journalId: number,
  summary: string,
  date: string
}

export interface ArticlesDTO {
  articles: Array<ArticleDTO>
}
