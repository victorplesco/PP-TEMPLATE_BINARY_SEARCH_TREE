require(ggplot2)

FIND_dtf  <- read.csv("~/BINARY-SEARCH-TREE/benchmark/Data/FIND.csv", header = FALSE); FIND_dtf <- FIND_dtf[, -11];
FIND_plot <- data.frame(Complexity = c(1:nrow(FIND_dtf)),
                        Median     = apply(X = FIND_dtf, MARGIN = 1, FUN = median),
                        Min        = apply(X = FIND_dtf, MARGIN = 1, FUN = min),
                        Max        = apply(X = FIND_dtf, MARGIN = 1, FUN = max));

BSC_dtf  <- read.csv("~/BINARY-SEARCH-TREE/benchmark/Data/BALANCE_BCS.csv", header = FALSE); BSC_dtf <- BSC_dtf[, -11];
BSC_plot <- data.frame(Complexity = c(1:nrow(BSC_dtf)),
                       Median     = apply(X = BSC_dtf, MARGIN = 1, FUN = median),
                       Min        = apply(X = BSC_dtf, MARGIN = 1, FUN = min),
                       Max        = apply(X = BSC_dtf, MARGIN = 1, FUN = max));

WSC_dtf  <- read.csv("~/BINARY-SEARCH-TREE/benchmark/Data/BALANCE_WCS.csv", header = FALSE); WSC_dtf <- WSC_dtf[, -11];
WSC_plot <- data.frame(Complexity = c(1:nrow(WSC_dtf)),
                       Median     = apply(X = WSC_dtf, MARGIN = 1, FUN = median),
                       Min        = apply(X = WSC_dtf, MARGIN = 1, FUN = min),
                       Max        = apply(X = WSC_dtf, MARGIN = 1, FUN = max));

TEN_dtf  <- read.csv("~/BINARY-SEARCH-TREE/benchmark/Data/INSERT_10.csv", header = FALSE); TEN_dtf <- TEN_dtf[, -11];
TEN_plot <- data.frame(Complexity = c(1:nrow(TEN_dtf)),
                       Median     = apply(X = TEN_dtf, MARGIN = 1, FUN = median),
                       Min        = apply(X = TEN_dtf, MARGIN = 1, FUN = min),
                       Max        = apply(X = TEN_dtf, MARGIN = 1, FUN = max));

THOUSAND_dtf  <- read.csv("~/BINARY-SEARCH-TREE/benchmark/Data/INSERT_1000.csv", header = FALSE); THOUSAND_dtf <- THOUSAND_dtf[, -11];
THOUSAND_plot <- data.frame(Complexity = c(1:nrow(THOUSAND_dtf)),
                            Median     = apply(X = THOUSAND_dtf, MARGIN = 1, FUN = median),
                            Min        = apply(X = THOUSAND_dtf, MARGIN = 1, FUN = min),
                            Max        = apply(X = THOUSAND_dtf, MARGIN = 1, FUN = max));

# FIND vs INSERT10 vs INSERT100;
(FINDvsINSERT_plot <- ggplot() +
   
   geom_line(data = FIND_plot,     aes(x = Complexity, y = Median), col = "indianred") +
   geom_line(data = TEN_plot,      aes(x = Complexity, y = Median), col = "#009dd0") +
   geom_line(data = THOUSAND_plot, aes(x = Complexity, y = Median), col = "#f58f3b") +
   
   # Custom Legend;
   geom_line(aes(x = c(200:300), y = rep(0.0295, length(c(200:300)))), size = 2, color = "indianred") + 
   geom_line(aes(x = c(200:300), y = rep(0.028,  length(c(200:300)))), size = 2, color = "#009dd0") + 
   geom_line(aes(x = c(200:300), y = rep(0.0265, length(c(200:300)))), size = 2, color = "#f58f3b") + 
   
   geom_text(aes(x = 500, y = 0.0295), label = "find()",       size = 4.5) +
   geom_text(aes(x = 620, y = 0.028),  label = "insert(10)",   size = 4.5) +
   geom_text(aes(x = 680, y = 0.0265), label = "insert(1000)", size = 4.5) +
   
   # Custom Labels;
   labs(title = "Median Time Detection",
        subtitle = "insert(10): ValueType = array[10], insert(1000): ValueType = array[1000], find()",
        x = "Complexity (Nodes)",
        y = "Time (Seconds)") +
   theme_bw(base_size = 17.5, base_family = "Times") +
   theme(legend.title = element_blank()));


# DIFFERENCE BETWEEN BALANCE and LIST balance();
LISTvsBALANCE <- data.frame(Complexity = c(1:10000),
                            Center     = WSC_plot$Median - BSC_plot$Median);

(LISTvsBALANCE_RIBBONplot <- ggplot(data = LISTvsBALANCE, aes(x = Complexity)) +

    geom_line(aes(y = Center), col = "indianred") +

    # Custom Labels;
    labs(title = "balance(): WCS - BCS",
         subtitle = "WCS = Worst Case Scenario (Balanced Tree); BCS = Best Case Scenario (Linked List).",
         x = "Complexity (Nodes)",
         y = "Time (Seconds)") +
    theme_bw(base_size = 17.5, base_family = "Times") +
    theme(legend.position = "none"));
