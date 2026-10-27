import "@fontsource/inter/400.css";
import "@fontsource/inter/500.css";
import "@fontsource/inter/600.css";
import "@fontsource/jetbrains-mono/400.css";
import "./index.css";

import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import { HashRouter, Route, Routes } from "react-router-dom";
import { DataProvider } from "./data";
import Layout from "./Layout";
import Benchmarks from "./pages/Benchmarks";
import CostModel from "./pages/CostModel";
import Inspector from "./pages/Inspector";
import LimitStudy from "./pages/LimitStudy";
import Overview from "./pages/Overview";

createRoot(document.getElementById("root")!).render(
  <StrictMode>
    <DataProvider>
      <HashRouter>
        <Routes>
          <Route element={<Layout />}>
            <Route index element={<Overview />} />
            <Route path="limit-study" element={<LimitStudy />} />
            <Route path="benchmarks" element={<Benchmarks />} />
            <Route path="inspector" element={<Inspector />} />
            <Route path="cost-model" element={<CostModel />} />
          </Route>
        </Routes>
      </HashRouter>
    </DataProvider>
  </StrictMode>,
);
