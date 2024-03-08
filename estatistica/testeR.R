library(shiny)
library(shinydashboard)
library(ggplot2) # pro gráfico de linha
# INITIALIZATION

data <- read.csv('df_stocks.csv')   # carrega o dataset
listaDeClasses = unique(data$Index) # pega o nome das classes (os nomes estão me index nesse caso)

min_time <- min(data$Date)
max_time <- max(data$Date)

dataFilter = data[data$Index == "FB" & data$Date >= min_time & data$Date <= max_time ,]

# USER INTERFACE
ui <- dashboardPage(
  dashboardHeader(),
  dashboardSidebar(),
  dashboardBody(
    
    # Inputs
    fluidRow( box( title="Selecione uma classe",width = 200,
      # select class  
      selectInput("Classe", label="Classe", choices=listaDeClasses, selected=listaDeClasses[0]),
      # select date
      sliderInput("DateRange", "Intervalo de tempo:", min = as.Date(min_time), max = as.Date(max_time),
                  value=c(as.Date(min_time), as.Date(max_time)), timeFormat="%d/%m/%y" )
    )),
    
    
    # plots      
    fluidRow(
      box(plotOutput("histo", height = 300)),
      box(plotOutput("lineg", height = 300)),
      box(plotOutput("boxpl", height = 300))
    ),
    
    # Medidas
    fluidRow(
      valueBox(30, "Média",        icon = icon("chart-bar"),       color="orange"),
      valueBox(30, "Moda",         icon = icon("chess-queen"),     color="purple"),
      valueBox(30, "Mediana",      icon = icon("star-half-stroke"),color="yellow"),
      valueBox(30, "Desvio Padrão",icon = icon("newspaper"),       color="blue"),
      valueBox(30, "Valor Máximo", icon = icon("circle-up"),       color="green"),
      valueBox(30, "Valor Mínimo", icon = icon("circle-down"),     color="red")
    )
    
  )
)





# SERVER // LOGIC
server <- function(input, output) { 
  
  min_time <- eventReactive(input$DateRange[1], {return (input$DateRange[1] ) })
  max_time <- eventReactive(input$DateRange[2], {return (input$DateRange[2] ) })
  
  output$histo <- renderPlot({
    dataFilter = data[data$Index == (input$Classe) & data$Date >= min_time() & data$Date <= max_time(),]
    hist(dataFilter$Close )
  })
  
  
  # output$lineg <- render
  
  
  
}

shinyApp(ui, server)