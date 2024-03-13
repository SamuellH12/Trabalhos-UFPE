# install.packages("shiny")
# install.packages("shinydashboard")
# install.packages("ggplot2")
# install.packages("dplyr")

library(shiny)
library(shinydashboard)
library(ggplot2)                # pro gráfico de linha
library(dplyr)                  # pra filtrar os dados


#------------------#
#  INITIALIZATION  #  
#------------------#

data <- read.csv('owid-covid-data.csv')   # carrega o dataset

listaDeClasses = c("Brazil", "European Union", "South Africa", "United States", "Australia", "China", "World", "Russia")
data <- data %>% filter(location %in% listaDeClasses) #filtrar os dados para trabalhar com um dataset menor
data <- data %>% filter(!if_any(new_cases_smoothed, is.na))
data <- data %>% filter(!if_any(new_deaths_smoothed, is.na))
listaDeClasses = unique(data$location) # pega o nome das classes (os nomes estão me region nesse caso)
data$date <- as.Date(data$date)

min_time <- min(data$date)
max_time <- max(data$date)


# Classes: $location
# Dados: $new_cases_smoothed


#------------------#
#  USER INTERFACE  #  
#------------------#

ui <- dashboardPage(
  dashboardHeader(disable = TRUE), #disable pra simplificar
  dashboardSidebar(disable = TRUE), # ^
  dashboardBody(
    
    # Inputs
    fluidRow( box( title="Selecione uma classe",width = 200,
                   # select class  
                   selectInput("Classe", label="Classe", choices=listaDeClasses, selected="Brazil"),
                   # select date
                   sliderInput("DateRange", "Intervalo de tempo:", min = as.Date(min_time), max = as.Date(max_time),
                               value=c(as.Date(min_time), as.Date(max_time)), timeFormat="%d/%m/%y" ),
    )),
    
    
    # plots      
    fluidRow(
      box(plotOutput("histo", height = 300)),
      box(plotOutput("histo2", height = 300)),
      box(plotOutput("lineg", height = 300)),
      box(plotOutput("lineg2", height = 300)),
      box(plotOutput("boxpl", height = 300)),
      box(plotOutput("boxpl2", height = 300))
    ),
    
    # Medidas
    fluidRow(
      titlePanel(h1("Medidas de Novos Casos por dia (suavizado)", style = "padding:0.25em; border:0.25em solid steelblue;")),
      valueBoxOutput("media"),
      valueBoxOutput("moda"),
      valueBoxOutput("mediana"),
      valueBoxOutput("desvio"),
      valueBoxOutput("valMax"),
      valueBoxOutput("valMin"),
    ),
    
    fluidRow(
      titlePanel(h1("Medidas de Novas Mortes por dia (suavizado)", style = "border-color:darkred; padding:0.25em; border:0.25em solid darkred;")),
      valueBoxOutput("media2"),
      valueBoxOutput("moda2"),
      valueBoxOutput("mediana2"),
      valueBoxOutput("desvio2"),
      valueBoxOutput("valMax2"),
      valueBoxOutput("valMin2")
    )
    
  )
)




#------------------#
#      SERVER      #  
#------------------#


server <- function(input, output) { 
  
  min_time <- eventReactive(input$DateRange[1], {return (input$DateRange[1] ) })
  max_time <- eventReactive(input$DateRange[2], {return (input$DateRange[2] ) })
  
  updatedData <- function(){
    return (data[data$location == (input$Classe) & data$date >= min_time() & data$date <= max_time(),])
  }
  
  #######  PLOTS  #######
  
  output$histo <- renderPlot({ hist(updatedData()$new_cases_smoothed ,col="steelblue",xlab="Casos", main="Quantidade de Casos por dia (suavizado)") })
  output$histo2<- renderPlot({ hist(updatedData()$new_deaths_smoothed,col="darkred",  xlab="Mortes",main="Quantidade de Mortes por dia (suavizado)")  })
  
  
  output$lineg <- renderPlot({
    dataL = updatedData();
    
    ggplot(data=dataL, aes(x=date)) + 
    geom_line(aes(y = dataL$new_cases_smoothed), color="steelblue") +
    xlab("Tempo") + ylab("Novos Casos (suavizado)")
  })
  
  output$lineg2 <- renderPlot({
    dataL = updatedData();
    
    ggplot(data=dataL, aes(x=date)) + 
    geom_line(aes(y = dataL$new_deaths_smoothed), color="darkred") +
    xlab("Tempo") + ylab("Novas Mortes (suavizado)")
  })

  
  output$boxpl <- renderPlot({ boxplot(updatedData()$new_cases_smoothed, col="steelblue", main="Casos por dia (suavizado)")  })
  output$boxpl2<- renderPlot({ boxplot(updatedData()$new_deaths_smoothed, col="darkred", main="Mortes por dia (suavizado)") })
  
  
  Mode <- function(x) {
    ux <- unique(x)
    ux[which.max(tabulate(match(x, ux)))]
  }
  
  #######  Medidas  #######
  
  output$media <- renderValueBox({ valueBox(round(mean(updatedData()$new_cases_smoothed),2), "Média",     icon=icon("chart-bar"),       color="orange") })
  output$moda  <- renderValueBox({ valueBox(round(Mode(updatedData()$new_cases_smoothed), 2), "Moda",      icon=icon("chess-queen"),     color="purple") })
  output$mediana<-renderValueBox({ valueBox(round(median(updatedData()$new_cases_smoothed),2),"Mediana",  icon=icon("star-half-stroke"),color="yellow") })
  output$desvio<- renderValueBox({ valueBox(round(sd(updatedData()$new_cases_smoothed),2),"Desvio Padrão",icon=icon("newspaper"),       color="blue") })
  output$valMax<- renderValueBox({ valueBox(round(max(updatedData()$new_cases_smoothed),2),"Valor Máximo",icon=icon("circle-up"),       color="green") })
  output$valMin<- renderValueBox({ valueBox(round(min(updatedData()$new_cases_smoothed),2),"Valor Mínimo",icon=icon("circle-down"),     color="red") })
  
  output$media2 <- renderValueBox({ valueBox(round(mean(updatedData()$new_deaths_smoothed),2), "Média",     icon=icon("chart-bar"),       color="orange") })
  output$moda2  <- renderValueBox({ valueBox(round(Mode(updatedData()$new_deaths_smoothed), 2), "Moda",      icon=icon("chess-queen"),     color="purple") })
  output$mediana2<-renderValueBox({ valueBox(round(median(updatedData()$new_deaths_smoothed),2),"Mediana",  icon=icon("star-half-stroke"),color="yellow") })
  output$desvio2<- renderValueBox({ valueBox(round(sd(updatedData()$new_deaths_smoothed),2),"Desvio Padrão",icon=icon("newspaper"),       color="blue") })
  output$valMax2<- renderValueBox({ valueBox(round(max(updatedData()$new_deaths_smoothed),2),"Valor Máximo",icon=icon("circle-up"),       color="green") })
  output$valMin2<- renderValueBox({ valueBox(round(min(updatedData()$new_deaths_smoothed),2),"Valor Mínimo",icon=icon("circle-down"),     color="red") })

}





shinyApp(ui, server)