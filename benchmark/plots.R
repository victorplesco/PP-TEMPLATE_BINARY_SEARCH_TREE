require(ggplot2)

FIND_dtf  <- read.csv("~/BINARY-SEARCH-TREE/benchmark/FIND.csv", header = FALSE); FIND_dtf <- FIND_dtf[, -11];
FIND_plot <- data.frame(Complexity = c(1:nrow(FIND_dtf)),
                        Mean       = apply(X = FIND_dtf, MARGIN = 1, FUN = mean),
                        Min        = apply(X = FIND_dtf, MARGIN = 1, FUN = min),
                        Max        = apply(X = FIND_dtf, MARGIN = 1, FUN = max));

ggplot(data = FIND_plot, aes(x = Complexity)) +
  
  # geom_line(aes(y = Mean), col = "#f58f3b") +
  geom_line(aes(y = Min),  col = "#009dd0") +
  # geom_line(aes(y = Max),  col = "#009dd0") +
  
  # Custom Labels;
  labs(title = "",
       subtitle = "",
       x = "Complexity (Nodes)",
       y = "Time (Seconds)") +
  theme_bw(base_size = 17.5, base_family = "Times");

BCS_dtf  <- read.csv("~/BINARY-SEARCH-TREE/benchmark/BALANCE_BCS.csv", header = FALSE); BCS_dtf <- BCS_dtf[, -11];
BSC_plot <- data.frame(Complexity = c(1:nrow(BCS_dtf)),
                       Mean       = apply(X = BCS_dtf, MARGIN = 1, FUN = mean),
                       Min        = apply(X = BCS_dtf, MARGIN = 1, FUN = min),
                       Max        = apply(X = BCS_dtf, MARGIN = 1, FUN = max));

ggplot(data = BSC_plot, aes(x = Complexity)) +
  
  geom_line(aes(y = Mean), col = "#f58f3b") +
  # geom_line(aes(y = Min),  col = "#009dd0") +
  # geom_line(aes(y = Max),  col = "indianred") +
  geom_line(data= FIND_plot, aes(y = Mean), col = "indianred") + 
  # Custom Labels;
  labs(title = "",
       subtitle = "",
       x = "Complexity (Nodes)",
       y = "Time (Seconds)") +
  theme_bw(base_size = 17.5, base_family = "Times");
