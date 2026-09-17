<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, viewport-fit=cover, user-scalable=no">
    <title>오늘근무 - 교대 캘린더 & 급여 계산기</title>

    <!-- iOS Safari & Android 홈 화면 추가 (단독 PWA 앱 규격) -->
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
    <meta name="apple-mobile-web-app-title" content="오늘근무">
    <meta name="mobile-web-app-capable" content="yes">
    <meta name="theme-color" content="#2563eb">

    <link rel="apple-touch-icon" href="data:image/svg+xml,<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 100 100'><rect width='100' height='100' rx='22' fill='%232563eb'/><text x='50%' y='68%' font-size='46' font-weight='900' fill='white' text-anchor='middle'>근무</text></svg>">
    <link rel="icon" type="image/svg+xml" href="data:image/svg+xml,<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 100 100'><rect width='100' height='100' rx='22' fill='%232563eb'/><text x='50%' y='68%' font-size='46' font-weight='900' fill='white' text-anchor='middle'>근무</text></svg>">

    <style>
        :root {
            --primary: #2563eb;
            --primary-dark: #1d4ed8;
            --day-color: #0284c7;
            --day-bg: #e0f2fe;
            --night-color: #7c3aed;
            --night-bg: #f3e8ff;
            --off-color: #64748b;
            --off-bg: #f1f5f9;
            --special-color: #ea580c;
            --special-bg: #ffedd5;
            --leave-color: #0d9488;
            --leave-bg: #ccfbf1;
            --no-ot-color: #d97706;
            --no-ot-bg: #fef3c7;
            --holiday-color: #e11d48;
            --bg-main: #f8fafc;
            --card-bg: #ffffff;
            --text-main: #0f172a;
            --text-sub: #64748b;
            --border: #e2e8f0;
        }

        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
            -webkit-tap-highlight-color: transparent;
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
        }

        body {
            background-color: var(--bg-main);
            color: var(--text-main);
            padding-top: env(safe-area-inset-top);
            padding-bottom: calc(28px + env(safe-area-inset-bottom));
            min-height: 100vh;
        }

        .container {
            max-width: 640px;
            margin: 0 auto;
            padding: 10px 14px;
        }

        .app-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 6px 0 10px 0;
        }

        .brand-box {
            display: flex;
            align-items: center;
            gap: 8px;
        }

        .brand-logo {
            width: 32px;
            height: 32px;
            background: linear-gradient(135deg, #2563eb, #1d4ed8);
            border-radius: 9px;
            color: white;
            font-weight: 900;
            font-size: 14px;
            display: flex;
            align-items: center;
            justify-content: center;
            box-shadow: 0 2px 5px rgba(37, 99, 235, 0.3);
        }

        .brand-title {
            font-size: 18px;
            font-weight: 800;
            color: #0f172a;
            letter-spacing: -0.5px;
        }

        .group-selector-wrap {
            display: flex;
            background: #e2e8f0;
            border-radius: 9999px;
            padding: 3px;
            gap: 2px;
        }

        .group-btn {
            border: none;
            background: transparent;
            font-size: 13px;
            font-weight: 800;
            padding: 6px 14px;
            border-radius: 9999px;
            color: #475569;
            cursor: pointer;
            transition: all 0.2s;
        }

        .group-btn.active {
            background: #ffffff;
            color: var(--primary);
            box-shadow: 0 2px 4px rgba(0,0,0,0.12);
        }

        .today-card {
            background: linear-gradient(135deg, #1e293b, #0f172a);
            color: #ffffff;
            border-radius: 14px;
            padding: 14px 16px;
            margin-bottom: 12px;
            display: flex;
            justify-content: space-between;
            align-items: center;
            box-shadow: 0 3px 6px rgba(15, 23, 42, 0.12);
        }

        .today-card .date-text {
            font-size: 12px;
            color: #94a3b8;
            margin-bottom: 2px;
        }

        .today-card .shift-text {
            font-size: 18px;
            font-weight: 800;
            color: #38bdf8;
            display: flex;
            align-items: center;
            gap: 6px;
        }

        .today-btn {
            background: rgba(255, 255, 255, 0.15);
            border: 1px solid rgba(255, 255, 255, 0.2);
            color: #f1f5f9;
            font-size: 12px;
            font-weight: 700;
            padding: 6px 12px;
            border-radius: 8px;
            cursor: pointer;
        }

        .main-tabs {
            display: grid;
            grid-template-columns: 1fr 1fr 1fr;
            background: #e2e8f0;
            border-radius: 12px;
            padding: 3px;
            margin-bottom: 12px;
            gap: 3px;
        }

        .main-tab-btn {
            border: none;
            background: transparent;
            padding: 10px 4px;
            border-radius: 9px;
            font-size: 13.5px;
            font-weight: 800;
            color: #475569;
            cursor: pointer;
            text-align: center;
            transition: all 0.2s;
        }

        .main-tab-btn.active {
            background: #ffffff;
            color: var(--primary);
            box-shadow: 0 2px 4px rgba(0,0,0,0.08);
        }

        .month-bar {
            display: flex;
            justify-content: space-between;
            align-items: center;
            background: #ffffff;
            padding: 10px 14px;
            border-radius: 12px;
            border: 1px solid var(--border);
            margin-bottom: 10px;
            box-shadow: 0 1px 2px rgba(0,0,0,0.03);
        }

        .month-title {
            font-size: 17px;
            font-weight: 800;
            letter-spacing: -0.5px;
        }

        .nav-btn {
            background: #f1f5f9;
            border: none;
            width: 34px;
            height: 34px;
            border-radius: 8px;
            font-size: 15px;
            font-weight: bold;
            color: #334155;
            cursor: pointer;
            display: flex;
            align-items: center;
            justify-content: center;
        }

        .leave-banner {
            background: linear-gradient(135deg, #0f766e, #115e59);
            color: #ffffff;
            border-radius: 12px;
            padding: 12px 16px;
            margin-bottom: 10px;
            display: flex;
            justify-content: space-between;
            align-items: center;
            box-shadow: 0 2px 4px rgba(15, 118, 110, 0.15);
            cursor: pointer;
        }

        .leave-banner .title {
            font-size: 12px;
            color: #99f6e4;
            margin-bottom: 3px;
            font-weight: 600;
        }

        .leave-banner .stats {
            font-size: 17px;
            font-weight: 800;
        }

        .leave-banner .sub {
            font-size: 11px;
            color: #ccfbf1;
            text-align: right;
        }

        .leave-banner .pay {
            font-size: 14px;
            font-weight: 800;
            color: #ffffff;
        }

        .stats-pills {
            display: grid;
            grid-template-columns: repeat(5, 1fr);
            gap: 6px;
            margin-bottom: 10px;
        }

        .stat-pill {
            background: #ffffff;
            border: 1px solid var(--border);
            border-radius: 10px;
            padding: 7px 4px;
            text-align: center;
        }

        .stat-pill .label {
            font-size: 10px;
            color: var(--text-sub);
            margin-bottom: 2px;
            font-weight: 700;
        }

        .stat-pill .val {
            font-size: 14px;
            font-weight: 800;
        }

        .calendar-card {
            background: #ffffff;
            border-radius: 14px;
            border: 1px solid var(--border);
            box-shadow: 0 2px 4px rgba(0,0,0,0.03);
            overflow: hidden;
            margin-bottom: 12px;
        }

        .cal-weekdays {
            display: grid;
            grid-template-columns: repeat(7, 1fr);
            text-align: center;
            background: #f8fafc;
            border-bottom: 1px solid var(--border);
            padding: 8px 0;
            font-size: 11px;
            font-weight: 700;
            color: #64748b;
        }

        .cal-weekdays div:first-child { color: #e11d48; }
        .cal-weekdays div:last-child { color: #0284c7; }

        .cal-grid {
            display: grid;
            grid-template-columns: repeat(7, 1fr);
        }

        .cal-day {
            min-height: 76px;
            padding: 4px 2px;
            border-right: 1px solid #f1f5f9;
            border-bottom: 1px solid #f1f5f9;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: flex-start;
            cursor: pointer;
            position: relative;
            background: #ffffff;
            transition: background 0.15s;
        }

        .cal-day:nth-child(7n) { border-right: none; }
        .cal-day.other-month { background: #fafafa; opacity: 0.35; }
        .cal-day.today { background: #eff6ff; }

        .day-num {
            font-size: 12px;
            font-weight: 700;
            margin-bottom: 2px;
        }

        .cal-day.sun .day-num { color: #e11d48; }
        .cal-day.sat .day-num { color: #0284c7; }
        .cal-day.holiday .day-num { color: #e11d48; font-weight: 900; }

        .holiday-name {
            font-size: 8.5px;
            color: #e11d48;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
            max-width: 95%;
            margin-bottom: 1px;
            font-weight: 700;
        }

        .shift-badge {
            font-size: 11px;
            font-weight: 800;
            padding: 3px 4px;
            border-radius: 6px;
            width: 92%;
            text-align: center;
            letter-spacing: -0.3px;
        }

        .shift-badge.day { background: var(--day-bg); color: var(--day-color); }
        .shift-badge.night { background: var(--night-bg); color: var(--night-color); }
        .shift-badge.off { background: var(--off-bg); color: var(--off-color); }
        .shift-badge.special { background: var(--special-bg); color: var(--special-color); border: 1px dashed var(--special-color); }
        .shift-badge.leave { background: var(--leave-bg); color: var(--leave-color); font-weight: 900; }
        .shift-badge.no-ot { background: var(--no-ot-bg); color: var(--no-ot-color); font-weight: 800; border: 1px dashed var(--no-ot-color); }
        .shift-badge.unpaid { background: #fee2e2; color: #b91c1c; font-weight: 800; }

        .sub-tag {
            font-size: 9px;
            color: var(--no-ot-color);
            font-weight: 800;
            margin-top: 1px;
        }

        .memo-tag {
            font-size: 8.5px;
            background: #fef08a;
            color: #854d0e;
            padding: 1px 4px;
            border-radius: 4px;
            margin-top: 2px;
            width: 92%;
            overflow: hidden;
            text-overflow: ellipsis;
            white-space: nowrap;
            font-weight: 800;
            text-align: center;
            border: 1px solid #fde047;
        }

        .card {
            background: #ffffff;
            border-radius: 14px;
            border: 1px solid var(--border);
            padding: 16px;
            margin-bottom: 14px;
            box-shadow: 0 1px 3px rgba(0,0,0,0.02);
        }

        .card-header {
            font-size: 14px;
            font-weight: 800;
            margin-bottom: 12px;
            display: flex;
            align-items: center;
            justify-content: space-between;
            border-bottom: 1px solid #f1f5f9;
            padding-bottom: 8px;
        }

        .salary-hero {
            background: linear-gradient(135deg, #0f172a, #1e293b);
            color: #ffffff;
            border-radius: 16px;
            padding: 20px;
            margin-bottom: 14px;
            box-shadow: 0 4px 10px rgba(15, 23, 42, 0.15);
        }

        .period-tag {
            font-size: 11px;
            background: rgba(255, 255, 255, 0.15);
            padding: 4px 8px;
            border-radius: 6px;
            display: inline-block;
            margin-bottom: 10px;
            font-weight: 700;
        }

        .hero-label {
            font-size: 12px;
            color: #94a3b8;
        }

        .hero-amount {
            font-size: 30px;
            font-weight: 800;
            color: #38bdf8;
            letter-spacing: -0.5px;
            margin: 4px 0 14px 0;
        }

        .hero-subgrid {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 10px;
            border-top: 1px solid #334155;
            padding-top: 10px;
        }

        .hero-subgrid .sub-val {
            font-size: 15px;
            font-weight: 800;
        }

        .pay-table {
            width: 100%;
            border-collapse: collapse;
            font-size: 12.5px;
        }

        .pay-table th {
            text-align: left;
            padding: 8px 6px;
            background: #f8fafc;
            color: #475569;
            font-weight: 700;
            border-bottom: 1px solid var(--border);
        }

        .pay-table td {
            padding: 8px 6px;
            border-bottom: 1px solid #f1f5f9;
        }

        .pay-table td.num {
            text-align: right;
            font-weight: 700;
            font-feature-settings: "tnum";
        }

        .pay-table tr.total-row {
            background: #f8fafc;
            font-weight: 800;
            border-top: 2px solid var(--border);
        }

        .pay-table tr.bonus-row {
            background: #faf5ff;
            color: #7c3aed;
            font-weight: 800;
        }

        .two-cols {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 10px;
            margin-bottom: 10px;
        }

        .input-group label {
            display: block;
            font-size: 12px;
            font-weight: 700;
            color: #334155;
            margin-bottom: 4px;
        }

        .input-group input, select, textarea {
            width: 100%;
            padding: 8px 10px;
            border-radius: 8px;
            border: 1px solid var(--border);
            font-size: 13px;
            font-weight: 700;
            color: var(--text-main);
            outline: none;
            background-color: #ffffff;
        }

        textarea {
            resize: vertical;
            min-height: 48px;
        }

        .toggle-box {
            display: flex;
            align-items: center;
            justify-content: space-between;
            background: #f8fafc;
            padding: 10px 12px;
            border-radius: 8px;
            border: 1px solid var(--border);
            margin-bottom: 10px;
            cursor: pointer;
        }

        .toggle-box label {
            font-size: 13px;
            font-weight: 800;
            cursor: pointer;
        }

        .toggle-box input[type="checkbox"] {
            width: 18px;
            height: 18px;
            accent-color: var(--primary);
            cursor: pointer;
        }

        .view-page {
            display: none;
        }

        .view-page.active {
            display: block;
        }

        .info-card {
            background: #f0fdf4;
            border: 1px solid #bbf7d0;
            border-radius: 10px;
            padding: 11px 13px;
            font-size: 11.5px;
            color: #166534;
            line-height: 1.5;
            margin-top: 10px;
        }

        .btn-action-group {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 10px;
            margin-top: 14px;
        }

        .btn-save {
            background: var(--primary);
            color: white;
            border: none;
            padding: 11px;
            border-radius: 10px;
            font-size: 14px;
            font-weight: 800;
            cursor: pointer;
            box-shadow: 0 2px 4px rgba(37, 99, 235, 0.2);
        }

        .btn-reset-data {
            background: #f1f5f9;
            color: #334155;
            border: 1px solid var(--border);
            padding: 11px;
            border-radius: 10px;
            font-size: 14px;
            font-weight: 800;
            cursor: pointer;
        }

        .modal-overlay {
            display: none;
            position: fixed;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background: rgba(0, 0, 0, 0.45);
            z-index: 200;
            align-items: flex-end;
            justify-content: center;
        }

        .modal-overlay.active {
            display: flex;
        }

        .modal-sheet {
            background: #ffffff;
            width: 100%;
            max-width: 500px;
            border-radius: 20px 20px 0 0;
            padding: 20px 18px calc(20px + env(safe-area-inset-bottom));
            animation: slideUp 0.22s ease-out;
            max-height: 90vh;
            overflow-y: auto;
        }

        @keyframes slideUp {
            from { transform: translateY(100%); }
            to { transform: translateY(0); }
        }

        .modal-title {
            font-size: 16px;
            font-weight: 800;
            margin-bottom: 12px;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }

        .modal-btn-grid {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 10px;
            margin-bottom: 12px;
        }

        .opt-btn {
            border: 1px solid var(--border);
            background: #f8fafc;
            border-radius: 12px;
            padding: 12px 10px;
            font-size: 13px;
            font-weight: 800;
            cursor: pointer;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            gap: 2px;
        }

        .opt-btn .desc-text {
            font-size: 10px;
            font-weight: normal;
            opacity: 0.8;
        }

        .opt-btn.day-sp { color: var(--special-color); border-color: #fdba74; background: #fff7ed; }
        .opt-btn.night-sp { color: #dc2626; border-color: #fca5a5; background: #fef2f2; }
        .opt-btn.leave { color: var(--leave-color); border-color: #99f6e4; background: #f0fdfa; }
        .opt-btn.half { color: #0284c7; border-color: #bae6fd; background: #f0f9ff; }
        .opt-btn.no-ot { color: var(--no-ot-color); border-color: #fde68a; background: #fffbeb; }
        .opt-btn.unpaid { color: #b91c1c; border-color: #fecaca; background: #fef2f2; }
        .opt-btn.off { color: #475569; }
        .opt-btn.reset { color: #64748b; grid-column: span 2; }
    </style>
</head>
<body>
    <div class="container">
        <!-- 상단 헤더 -->
        <div class="app-header">
            <div class="brand-box">
                <div class="brand-logo">근무</div>
                <div class="brand-title">오늘근무</div>
            </div>
            <div class="group-selector-wrap">
                <button class="group-btn" id="btn-grp-A" onclick="setGroup('A')">A조</button>
                <button class="group-btn" id="btn-grp-B" onclick="setGroup('B')">B조</button>
                <button class="group-btn active" id="btn-grp-C" onclick="setGroup('C')">C조</button>
            </div>
        </div>

        <!-- 오늘 내 근무 현황 카드 -->
        <div class="today-card">
            <div>
                <div class="date-text" id="today-date-text">2026년 9월 16일 (수)</div>
                <div class="shift-text">
                    <span id="today-group-badge">C조</span>
                    <span id="today-shift-badge">야간 2일차 🌙</span>
                </div>
            </div>
            <button class="today-btn" onclick="goToToday()">오늘 보기</button>
        </div>

        <!-- 3대 메인 탭 -->
        <div class="main-tabs">
            <button class="main-tab-btn active" id="tab-btn-cal" onclick="switchView('calendar')">📅 교대 캘린더</button>
            <button class="main-tab-btn" id="tab-btn-pay" onclick="switchView('payroll')">💰 급여 계산기</button>
            <button class="main-tab-btn" id="tab-btn-leave" onclick="switchView('leave')">🏖️ 연차 & 설정</button>
        </div>

        <!-- 1. 교대 캘린더 화면 -->
        <section id="view-calendar" class="view-page active">
            <div class="leave-banner" onclick="switchView('leave')">
                <div>
                    <div class="title">🏖️ 회계연도 기준 연차 현황 (터치하여 설정)</div>
                    <div class="stats">잔여: <span id="banner-remain-leave">0</span>일 <span style="font-size:12px; font-weight:normal; opacity:0.9;">(총 <span id="banner-total-leave">0</span> / 사용 <span id="banner-used-leave">0</span>)</span></div>
                </div>
                <div class="sub">
                    <div>미사용 연차수당</div>
                    <div class="pay" id="banner-leave-pay">0원</div>
                </div>
            </div>

            <div class="month-bar">
                <button class="nav-btn" onclick="changeMonth(-1)">◀</button>
                <div class="month-title" id="cal-month-title">2026년 9월</div>
                <button class="nav-btn" onclick="changeMonth(1)">▶</button>
            </div>

            <div class="stats-pills">
                <div class="stat-pill"><div class="label">주간</div><div class="val" id="pill-day" style="color:var(--day-color);">0</div></div>
                <div class="stat-pill"><div class="label">야간</div><div class="val" id="pill-night" style="color:var(--night-color);">0</div></div>
                <div class="stat-pill"><div class="label">특근</div><div class="val" id="pill-special" style="color:var(--special-color);">0</div></div>
                <div class="stat-pill"><div class="label">휴무</div><div class="val" id="pill-off" style="color:var(--off-color);">0</div></div>
                <div class="stat-pill"><div class="label">연차</div><div class="val" id="pill-leave" style="color:var(--leave-color);">0</div></div>
            </div>

            <div class="calendar-card">
                <div class="cal-weekdays">
                    <div>일</div><div>월</div><div>화</div><div>수</div><div>목</div><div>금</div><div>토</div>
                </div>
                <div class="cal-grid" id="calendar-grid"></div>
            </div>
            <div style="font-size: 11.5px; color: var(--text-sub); text-align: center; line-height: 1.6; margin-bottom: 10px;">
                💡 <strong>날짜 터치:</strong> 휴무일에도 <strong>특근(주특/야특)</strong> 설정이 가능하며, <strong>메모 및 연차, 반차, O.T해제</strong>를 변경할 수 있습니다.<br>
                💡 <strong>연장 제외:</strong> <strong>연차 / 반차 / O.T 해제</strong> 적용 시 1일 2.5h 연장수당이 급여 계산에서 자동 제외됩니다.
            </div>
        </section>

        <!-- 2. 급여 계산기 화면 -->
        <section id="view-payroll" class="view-page">
            <div class="month-bar">
                <button class="nav-btn" onclick="changePayMonth(-1)">◀</button>
                <div class="month-title" id="pay-month-title">2026년 9월 급여</div>
                <button class="nav-btn" onclick="changePayMonth(1)">▶</button>
            </div>

            <!-- 세전 총지급액 / 급여 / 상여금 중심의 히어로 카드 -->
            <div class="salary-hero">
                <div class="period-tag" id="pay-period-label">산정기간: 2026-08-16 ~ 2026-09-15</div>
                <div class="hero-label">총 지급액 (세전 합계)</div>
                <div class="hero-amount" id="hero-gross-pay">0 원</div>
                <div class="hero-subgrid">
                    <div>
                        <div class="hero-label">월 급여 (수당 포함)</div>
                        <div class="sub-val" id="hero-regular-pay" style="color: #38bdf8;">0 원</div>
                    </div>
                    <div>
                        <div class="hero-label">상여금 (지급월 대상)</div>
                        <div class="sub-val" id="hero-bonus-pay" style="color: #c084fc;">0 원</div>
                    </div>
                </div>
            </div>

            <div class="card">
                <div class="card-header">
                    <span>1. 출근 및 수당 입력 (16일~15일 자동 연동)</span>
                    <button style="border:none; background:none; color:var(--primary); font-size:11px; font-weight:bold; cursor:pointer;" onclick="syncFromCalendar()">캘린더에서 재동기화</button>
                </div>
                <div class="two-cols">
                    <div class="input-group">
                        <label>주간 근무일수 [E2]</label>
                        <input type="number" id="inp-day-days" value="0" min="0" oninput="calculatePayrollFromInputs()">
                    </div>
                    <div class="input-group">
                        <label>야간 근무일수 [E3]</label>
                        <input type="number" id="inp-night-days" value="0" min="0" oninput="calculatePayrollFromInputs()">
                    </div>
                </div>
                <div class="two-cols">
                    <div class="input-group">
                        <label>주간 특근일수 [E4]</label>
                        <input type="number" id="inp-daysp-days" value="0" min="0" oninput="calculatePayrollFromInputs()">
                    </div>
                    <div class="input-group">
                        <label>야간 특근일수 [E5]</label>
                        <input type="number" id="inp-nightsp-days" value="0" min="0" oninput="calculatePayrollFromInputs()">
                    </div>
                </div>
                <div class="two-cols">
                    <div class="input-group">
                        <label>O.T 해제 및 연차 일수 (2.5h 제외)</label>
                        <input type="number" id="inp-no-ot-days" value="0" min="0" oninput="calculatePayrollFromInputs()">
                    </div>
                    <div class="input-group">
                        <label>실제 적용 연장시간 (1.5배)</label>
                        <input type="text" id="disp-ot-hours" value="0.0h" readonly style="background:#f1f5f9; color:var(--primary); font-weight:800;">
                    </div>
                </div>

                <div class="two-cols">
                    <div class="input-group">
                        <label>명절근무수당 (원)</label>
                        <input type="number" id="inp-holiday-bonus" value="0" step="10000" min="0" oninput="calculatePayrollFromInputs()" placeholder="예: 50000">
                    </div>
                    <div class="input-group">
                        <label>입사년월일 (연차·소급 판정)</label>
                        <input type="date" id="inp-hire-date" onchange="onPayrollHireDateChange()">
                    </div>
                </div>

                <div class="toggle-box" onclick="toggleBonusCheck()">
                    <label for="inp-bonus-check">짝수달 상여금 50% 지급 (근속수당 가산)</label>
                    <input type="checkbox" id="inp-bonus-check" onchange="calculatePayrollFromInputs()">
                </div>
                <div class="toggle-box" onclick="toggleRetroCheck()">
                    <label for="inp-retro-check">기타소급적용 (17년 이전 입사자 대상 보전금)</label>
                    <input type="checkbox" id="inp-retro-check" onchange="calculatePayrollFromInputs()">
                </div>

                <div class="btn-action-group">
                    <button class="btn-save" onclick="manualSaveData()">💾 입력값 저장</button>
                    <button class="btn-reset-data" onclick="resetDefaults()">🔄 초기화(기본값)</button>
                </div>
            </div>

            <div class="card">
                <div class="card-header">
                    <span>2. 지급 상세 내역 (세전)</span>
                    <span id="bonus-badge" style="font-size: 11px; padding: 2px 6px; border-radius: 4px; background: #faf5ff; color: #7c3aed; font-weight: 800;">짝수달 상여</span>
                </div>
                <table class="pay-table">
                    <tbody>
                        <tr><td>기본급 (209h)</td><td class="num" id="row-base-pay">0</td></tr>
                        <tr><td>직책수당</td><td class="num" id="row-duty-pay">0</td></tr>
                        <tr><td>근속수당</td><td class="num" id="row-seniority-pay">0</td></tr>
                        <tr><td>연장수당 (통상×1.5×연장h)</td><td class="num" id="row-ot-pay">0</td></tr>
                        <tr><td>야간수당 (통상×0.5×7.0h)</td><td class="num" id="row-night-pay">0</td></tr>
                        <tr><td>휴일수당 (통상×1.5×8.0h)</td><td class="num" id="row-hol-pay">0</td></tr>
                        <tr><td>휴일연장수당 (통상×2.0×2.5h)</td><td class="num" id="row-hol-ot-pay">0</td></tr>
                        <tr><td>휴일야간수당 (통상×0.5×7.0h)</td><td class="num" id="row-hol-night-pay">0</td></tr>
                        <tr style="background:#f0fdf4;">
                            <td><strong>명절근무수당</strong></td>
                            <td class="num" id="row-holiday-bonus" style="color:#166534; font-weight:800;">0</td>
                        </tr>
                        <tr style="background:#fefce8;">
                            <td><strong>기타소급적용 (17년 이전 입사자)</strong></td>
                            <td class="num" id="row-other-pay" style="color:#b45309; font-weight:800;">0</td>
                        </tr>
                        <tr class="bonus-row"><td>상여금 (기본급 50% + 근속수당)</td><td class="num" id="row-bonus-pay">0</td></tr>
                        <tr class="total-row"><td>총 지급액 (세전)</td><td class="num" id="row-gross-pay" style="color:var(--primary); font-size:14px;">0</td></tr>
                    </tbody>
                </table>
            </div>
        </section>

        <!-- 3. 연차 & 설정 화면 -->
        <section id="view-leave" class="view-page">
            <div class="card">
                <div class="card-header">
                    <span>회계연도 기준 연차 자동 계산</span>
                    <span style="font-size: 11px; color: var(--leave-color); font-weight: bold;">매년 1월 1일 정산</span>
                </div>

                <div class="two-cols" style="align-items:center;">
                    <div class="input-group">
                        <label>입사년월일 선택</label>
                        <input type="date" id="input-hire-date" onchange="onHireDateChange()">
                    </div>
                    <div class="input-group">
                        <label>총 부여 연차 (자동계산/수정가능)</label>
                        <input type="number" id="input-total-leave" value="0" step="0.5" min="0" onchange="saveLeaveConfig()" placeholder="예: 19">
                    </div>
                </div>

                <div class="info-card" id="leave-calc-info-box">
                    📅 <strong>회계연도 기준(매년 1월 1일 정산):</strong> 전사원 일괄 정산되는 회계일 기준 연차 공식이 적용됩니다.
                </div>

                <div style="display: grid; grid-template-columns: repeat(3, 1fr); gap: 6px; margin: 12px 0; text-align: center;">
                    <div style="background:#f8fafc; border:1px solid var(--border); border-radius:10px; padding:8px 4px;">
                        <div style="font-size:11px; color:var(--text-sub);">총 연차</div>
                        <div style="font-size:16px; font-weight:800;" id="stat-total-leave">0일</div>
                    </div>
                    <div style="background:#f8fafc; border:1px solid var(--border); border-radius:10px; padding:8px 4px;">
                        <div style="font-size:11px; color:var(--text-sub);">사용 연차</div>
                        <div style="font-size:16px; font-weight:800; color:#ea580c;" id="stat-used-leave">0일</div>
                    </div>
                    <div style="background:#f8fafc; border:1px solid var(--border); border-radius:10px; padding:8px 4px;">
                        <div style="font-size:11px; color:var(--text-sub);">잔여 연차</div>
                        <div style="font-size:16px; font-weight:800; color:var(--leave-color);" id="stat-remain-leave">0일</div>
                    </div>
                </div>

                <div style="background: #f0fdfa; border: 1px solid #ccfbf1; border-radius: 10px; padding: 12px;">
                    <div style="font-size: 12px; color: #0f766e; margin-bottom: 4px;">미사용 연차수당 공식: 8시간 × 통상시급 × 잔여일수</div>
                    <div style="display: flex; justify-content: space-between; font-size: 12.5px; margin-bottom: 4px;">
                        <span>1일 연차 단가 (8h):</span>
                        <strong id="val-leave-daily-rate">0원</strong>
                    </div>
                    <div style="display: flex; justify-content: space-between; font-size: 15px; font-weight: 800; color: #0f766e;">
                        <span>총 예상 연차수당:</span>
                        <span id="val-total-leave-pay">0원</span>
                    </div>
                </div>
            </div>

            <div class="card">
                <div class="card-header">
                    <span>급여 기준 단가 설정 (예시 가이드 적용)</span>
                    <button style="border: none; background: none; color: var(--primary); font-size: 11px; font-weight: bold; cursor: pointer;" onclick="resetDefaults()">기본값(0) 복원</button>
                </div>
                <div class="two-cols">
                    <div class="input-group">
                        <label>기준 기본시급 [B7] (예: 최저 10,320)</label>
                        <input type="number" id="input-base-hourly" value="0" step="10" onchange="saveWageConfig()" placeholder="예: 10320">
                    </div>
                    <div class="input-group">
                        <label>통상임금(시급) [B8] (예: 11,000원)</label>
                        <input type="number" id="input-ordinary-hourly" value="0" step="1" onchange="saveWageConfig()" placeholder="예: 11000">
                    </div>
                </div>
                <div class="two-cols">
                    <div class="input-group">
                        <label>월 기준시간</label>
                        <input type="number" id="input-base-hours" value="209" onchange="saveWageConfig()">
                    </div>
                    <div class="input-group">
                        <label>직책수당 (원)</label>
                        <input type="number" id="input-duty-pay" value="0" step="1000" onchange="saveWageConfig()" placeholder="예: 70000">
                    </div>
                </div>
                <div class="two-cols">
                    <div class="input-group">
                        <label>근속수당 (원)</label>
                        <input type="number" id="input-seniority-pay" value="0" step="1000" onchange="saveWageConfig()" placeholder="예: 70000">
                    </div>
                    <div class="input-group">
                        <label>기타소급 적용 상태</label>
                        <input type="text" id="disp-retro-status" value="미적용 (17년 이후 입사)" readonly style="background:#f1f5f9; font-weight:800;">
                    </div>
                </div>

                <div class="btn-action-group">
                    <button class="btn-save" onclick="manualSaveData()">💾 설정 저장</button>
                    <button class="btn-reset-data" onclick="resetDefaults()">🔄 초기화(기본값)</button>
                </div>
            </div>

            <div class="card">
                <div class="card-header"><span>회계연도 연차 및 사내 규정 안내</span></div>
                <div style="font-size: 12px; color: var(--text-sub); line-height: 1.65;">
                    • <strong>회계연도 기준(매년 1월 1일):</strong> 전사원이 동일하게 1월 1일 기준으로 연차가 정산되며, 2015년 6월 16일 입사자 기준 2026년 정기부여분 <strong>19일</strong>이 정확히 산출됩니다.<br>
                    • <strong>스케줄러 메모 기능:</strong> 캘린더 날짜를 터치하여 메모를 입력하면 날짜 칸에 📝 뱃지로 표시됩니다.<br>
                    • <strong>시급/통상시급 가이드:</strong> 기본시급 예시는 최저시급(10,320원), 통상시급은 11,000원 예시를 참고하여 자유롭게 입력하실 수 있습니다.<br>
                    • <strong>저장 및 초기화:</strong> 입력하신 모든 시급, 연차, 수당, 메모는 💾 [설정 저장] 버튼을 통해 브라우저에 안전하게 보존됩니다.
                </div>
            </div>
        </section>
    </div>

    <!-- 근태 및 메모(스케줄러) 변경 모달 시트 -->
    <div class="modal-overlay" id="modal-override" onclick="closeModal(event)">
        <div class="modal-sheet" onclick="event.stopPropagation()">
            <div class="modal-title">
                <div>
                    <span id="modal-date-text">2026년 9월 16일 (수)</span>
                    <span id="modal-orig-text" style="font-size: 12px; color: var(--text-sub); font-weight: normal; margin-left: 6px;">[기본: 야간]</span>
                </div>
                <button style="border: none; background: none; font-size: 16px; color: #94a3b8; cursor: pointer;" onclick="closeModalDirect()">✕</button>
            </div>
            
            <div style="margin-bottom: 14px;">
                <label style="display:block; font-size:12px; font-weight:800; color:#334155; margin-bottom:4px;">📝 일자별 메모 (스케줄러 기능)</label>
                <textarea id="modal-memo-input" placeholder="예: 설비 점검, 연차 신청, 특근 신청 등 메모 입력..." oninput="onMemoInputChange()"></textarea>
            </div>

            <div style="font-size:12px; font-weight:800; color:#334155; margin-bottom:6px;">근무 변경 옵션</div>
            <div class="modal-btn-grid">
                <button class="opt-btn day-sp" onclick="setDayOverride('SPECIAL_DAY')">
                    <span>☀️ 주간 특근</span>
                    <span class="desc-text">휴일 주간 10.5h</span>
                </button>
                <button class="opt-btn night-sp" onclick="setDayOverride('SPECIAL_NIGHT')">
                    <span>🌙 야간 특근</span>
                    <span class="desc-text">휴일 야간 10.5h</span>
                </button>
                <button class="opt-btn leave" onclick="setDayOverride('LEAVE')">
                    <span>🌴 연차</span>
                    <span class="desc-text">-1일 (2.5h OT 제외)</span>
                </button>
                <button class="opt-btn half" onclick="setDayOverride('HALF_LEAVE')">
                    <span>⏱️ 반차</span>
                    <span class="desc-text">-0.5일 (2.5h OT 제외)</span>
                </button>
                <button class="opt-btn no-ot" onclick="setDayOverride('NO_OT')">
                    <span>⏹️ O.T 해제</span>
                    <span class="desc-text">정시퇴근 (2.5h OT 제외)</span>
                </button>
                <button class="opt-btn unpaid" onclick="setDayOverride('UNPAID_OFF')">
                    <span>🚫 무급 휴무</span>
                    <span class="desc-text">무급결근 (수당 제외)</span>
                </button>
                <button class="opt-btn off" onclick="setDayOverride('FORCED_OFF')">
                    <span>🛌 강제 휴무</span>
                    <span class="desc-text">비번/휴무 처리</span>
                </button>
                <button class="opt-btn reset" onclick="setDayOverride(null)">
                    <span>🔄 기본 스케줄로 복구</span>
                </button>
            </div>
        </div>
    </div>

    <script>
        const BASE_DATE = new Date(2026, 8, 9); // 2026-09-09
        const GROUP_OFFSETS = { 'C': 0, 'B': 4, 'A': 8 };

        const SHUTDOWN_DAYS = new Set([
            '2025-01-28', '2025-01-29', '2025-01-30',
            '2025-10-05', '2025-10-06', '2025-10-07',
            '2026-02-16', '2026-02-17', '2026-02-18',
            '2026-09-24', '2026-09-25', '2026-09-26',
            '2027-02-06', '2027-02-07', '2027-02-08',
            '2027-09-14', '2027-09-15', '2027-09-16'
        ]);

        const HOLIDAYS = {
            '2025-01-01': { name: '신정', type: 'STATUTORY' },
            '2025-01-28': { name: '설날연휴', type: 'MAIN_HOLIDAY' },
            '2025-01-29': { name: '설날', type: 'MAIN_HOLIDAY' },
            '2025-01-30': { name: '설날연휴', type: 'MAIN_HOLIDAY' },
            '2025-03-01': { name: '삼일절', type: 'STATUTORY' },
            '2025-03-03': { name: '대체공휴일', type: 'STATUTORY' },
            '2025-05-05': { name: '어린이날', type: 'STATUTORY' },
            '2025-05-06': { name: '부처님오신날', type: 'STATUTORY' },
            '2025-06-06': { name: '현충일', type: 'STATUTORY' },
            '2025-08-15': { name: '광복절', type: 'STATUTORY' },
            '2025-10-03': { name: '개천절', type: 'STATUTORY' },
            '2025-10-05': { name: '추석연휴', type: 'MAIN_HOLIDAY' },
            '2025-10-06': { name: '추석', type: 'MAIN_HOLIDAY' },
            '2025-10-07': { name: '추석연휴', type: 'MAIN_HOLIDAY' },
            '2025-10-08': { name: '대체공휴일(추석)', type: 'STATUTORY' },
            '2025-10-09': { name: '한글날', type: 'STATUTORY' },
            '2025-12-25': { name: '성탄절', type: 'STATUTORY' },

            '2026-01-01': { name: '신정', type: 'STATUTORY' },
            '2026-02-16': { name: '설날연휴', type: 'MAIN_HOLIDAY' },
            '2026-02-17': { name: '설날', type: 'MAIN_HOLIDAY' },
            '2026-02-18': { name: '설날연휴', type: 'MAIN_HOLIDAY' },
            '2026-03-01': { name: '삼일절', type: 'STATUTORY' },
            '2026-03-02': { name: '대체공휴일', type: 'STATUTORY' },
            '2026-05-05': { name: '어린이날', type: 'STATUTORY' },
            '2026-05-24': { name: '부처님오신날', type: 'STATUTORY' },
            '2026-05-25': { name: '대체공휴일', type: 'STATUTORY' },
            '2026-06-06': { name: '현충일', type: 'STATUTORY' },
            '2026-08-15': { name: '광복절', type: 'STATUTORY' },
            '2026-08-17': { name: '대체공휴일', type: 'STATUTORY' },
            '2026-09-24': { name: '추석연휴', type: 'MAIN_HOLIDAY' },
            '2026-09-25': { name: '추석', type: 'MAIN_HOLIDAY' },
            '2026-09-26': { name: '추석연휴', type: 'MAIN_HOLIDAY' },
            '2026-09-28': { name: '대체공휴일(추석)', type: 'STATUTORY' },
            '2026-10-03': { name: '개천절', type: 'STATUTORY' },
            '2026-10-05': { name: '대체공휴일', type: 'STATUTORY' },
            '2026-10-09': { name: '한글날', type: 'STATUTORY' },
            '2026-12-25': { name: '성탄절', type: 'STATUTORY' },

            '2027-01-01': { name: '신정', type: 'STATUTORY' },
            '2027-02-06': { name: '설날연휴', type: 'MAIN_HOLIDAY' },
            '2027-02-07': { name: '설날', type: 'MAIN_HOLIDAY' },
            '2027-02-08': { name: '설날연휴', type: 'MAIN_HOLIDAY' },
            '2027-02-09': { name: '대체공휴일(설날)', type: 'STATUTORY' },
            '2027-03-01': { name: '삼일절', type: 'STATUTORY' },
            '2027-05-05': { name: '어린이날', type: 'STATUTORY' },
            '2027-05-13': { name: '부처님오신날', type: 'STATUTORY' },
            '2027-06-06': { name: '현충일', type: 'STATUTORY' },
            '2027-06-07': { name: '대체공휴일', type: 'STATUTORY' },
            '2027-08-15': { name: '광복절', type: 'STATUTORY' },
            '2027-08-16': { name: '대체공휴일', type: 'STATUTORY' },
            '2027-09-14': { name: '추석연휴', type: 'MAIN_HOLIDAY' },
            '2027-09-15': { name: '추석', type: 'MAIN_HOLIDAY' },
            '2027-09-16': { name: '추석연휴', type: 'MAIN_HOLIDAY' },
            '2027-09-17': { name: '대체공휴일(추석)', type: 'STATUTORY' },
            '2027-10-03': { name: '개천절', type: 'STATUTORY' },
            '2027-10-04': { name: '대체공휴일', type: 'STATUTORY' },
            '2027-10-09': { name: '한글날', type: 'STATUTORY' },
            '2027-10-11': { name: '대체공휴일', type: 'STATUTORY' },
            '2027-12-25': { name: '성탄절', type: 'STATUTORY' }
        };

        let currentGroup = 'C';
        let currentCalDate = new Date(2026, 8, 1);
        let currentPayDate = new Date(2026, 8, 1);
        let selectedDateStr = null;

        let overrides = {};
        let dayMemos = {};
        let config = {
            hireDate: '',
            totalLeave: 0,
            baseHourly: 0,
            ordinaryHourly: 0,
            baseHours: 209,
            dutyPay: 0,
            seniorityPay: 0,
            applyRetroPay: false,
            holidayBonus: 0
        };

        function fmt(n) { return Math.round(n).toLocaleString('ko-KR'); }
        function toDateKey(y, m, d) {
            return `${y}-${String(m + 1).padStart(2, '0')}-${String(d).padStart(2, '0')}`;
        }

        function getBaseShift(date, group) {
            const dateStr = toDateKey(date.getFullYear(), date.getMonth(), date.getDate());

            if (SHUTDOWN_DAYS.has(dateStr)) {
                return { type: 'OFF', name: '휴무', isShutdown: true };
            }

            const offset = GROUP_OFFSETS[group];
            const targetMs = Date.UTC(date.getFullYear(), date.getMonth(), date.getDate());
            const baseMs = Date.UTC(BASE_DATE.getFullYear(), BASE_DATE.getMonth(), BASE_DATE.getDate());

            let effectiveDays = 0;
            if (targetMs >= baseMs) {
                let currMs = baseMs;
                while (currMs < targetMs) {
                    const cDt = new Date(currMs);
                    const cStr = toDateKey(cDt.getUTCFullYear(), cDt.getUTCMonth(), cDt.getUTCDate());
                    if (!SHUTDOWN_DAYS.has(cStr)) {
                        effectiveDays++;
                    }
                    currMs += 86400000;
                }
            } else {
                let currMs = targetMs;
                while (currMs < baseMs) {
                    const cDt = new Date(currMs);
                    const cStr = toDateKey(cDt.getUTCFullYear(), cDt.getUTCMonth(), cDt.getUTCDate());
                    if (!SHUTDOWN_DAYS.has(cStr)) {
                        effectiveDays--;
                    }
                    currMs += 86400000;
                }
            }

            let idx = (effectiveDays + offset) % 12;
            if (idx < 0) idx += 12;

            if (idx >= 0 && idx <= 3) return { type: 'DAY', name: '주간', dayNum: idx + 1 };
            if (idx >= 4 && idx <= 5) return { type: 'OFF', name: '휴무', dayNum: idx - 3 };
            if (idx >= 6 && idx <= 9) return { type: 'NIGHT', name: '야간', dayNum: idx - 5 };
            return { type: 'OFF', name: '휴무', dayNum: idx - 9 };
        }

        function getActualShift(date, group) {
            const dateStr = toDateKey(date.getFullYear(), date.getMonth(), date.getDate());
            const base = getBaseShift(date, group);
            const holiday = HOLIDAYS[dateStr] || null;

            if (overrides[dateStr]) {
                const ov = overrides[dateStr];
                if (ov === 'SPECIAL_DAY') return { type: 'SPECIAL_DAY', name: '주특', isSpecial: true, hasOt: true, holidayName: holiday ? holiday.name : '' };
                if (ov === 'SPECIAL_NIGHT') return { type: 'SPECIAL_NIGHT', name: '야특', isSpecial: true, hasOt: true, holidayName: holiday ? holiday.name : '' };
                if (ov === 'LEAVE') return { type: 'LEAVE', name: '연차', isLeave: true, leaveVal: 1.0, hasOt: false, holidayName: holiday ? holiday.name : '' };
                if (ov === 'HALF_LEAVE') return { type: 'HALF_LEAVE', name: '반차', isLeave: true, leaveVal: 0.5, hasOt: false, holidayName: holiday ? holiday.name : '' };
                if (ov === 'NO_OT') return { type: 'NO_OT', name: base.type === 'NIGHT' ? '야간' : '주간', subName: 'O.T해제', isNoOt: true, hasOt: false, origType: base.type, holidayName: holiday ? holiday.name : '' };
                if (ov === 'UNPAID_OFF') return { type: 'UNPAID_OFF', name: '무급', isUnpaid: true, hasOt: false, holidayName: holiday ? holiday.name : '' };
                if (ov === 'FORCED_OFF') return { type: 'OFF', name: '휴무', isOff: true, hasOt: false, holidayName: holiday ? holiday.name : '' };
            }

            if (base.type === 'OFF') {
                return { ...base, isHoliday: !!holiday, holidayName: holiday ? holiday.name : '' };
            }

            if (holiday) {
                if (base.type === 'DAY') return { type: 'SPECIAL_DAY', name: '주특', isSpecial: true, isHoliday: true, hasOt: true, holidayName: holiday.name };
                if (base.type === 'NIGHT') return { type: 'SPECIAL_NIGHT', name: '야특', isSpecial: true, isHoliday: true, hasOt: true, holidayName: holiday.name };
            }

            return { ...base, hasOt: true, isHoliday: !!holiday, holidayName: holiday ? holiday.name : '' };
        }

        function renderCalendar() {
            const year = currentCalDate.getFullYear();
            const month = currentCalDate.getMonth();
            document.getElementById('cal-month-title').innerText = `${year}년 ${month + 1}월`;

            const firstDayIndex = new Date(year, month, 1).getDay();
            const lastDate = new Date(year, month + 1, 0).getDate();
            const prevLastDate = new Date(year, month, 0).getDate();

            const grid = document.getElementById('calendar-grid');
            grid.innerHTML = '';
            const today = new Date();
            const todayStr = toDateKey(today.getFullYear(), today.getMonth(), today.getDate());

            let counts = { day: 0, night: 0, special: 0, off: 0, leave: 0 };

            for (let i = firstDayIndex - 1; i >= 0; i--) {
                const d = prevLastDate - i;
                const cell = document.createElement('div');
                cell.className = 'cal-day other-month';
                cell.innerHTML = `<span class="day-num">${d}</span>`;
                grid.appendChild(cell);
            }

            for (let d = 1; d <= lastDate; d++) {
                const dateObj = new Date(year, month, d);
                const dayOfWeek = dateObj.getDay();
                const dateStr = toDateKey(year, month, d);
                const shift = getActualShift(dateObj, currentGroup);

                if (shift.type === 'DAY' || (shift.type === 'NO_OT' && shift.origType !== 'NIGHT')) counts.day++;
                else if (shift.type === 'NIGHT' || (shift.type === 'NO_OT' && shift.origType === 'NIGHT')) counts.night++;
                else if (shift.type === 'SPECIAL_DAY' || shift.type === 'SPECIAL_NIGHT') counts.special++;
                else if (shift.type === 'OFF' || shift.type === 'UNPAID_OFF') counts.off++;
                else if (shift.type === 'LEAVE') counts.leave += 1.0;
                else if (shift.type === 'HALF_LEAVE') counts.leave += 0.5;

                const cell = document.createElement('div');
                let cellClasses = ['cal-day'];
                if (dayOfWeek === 0) cellClasses.push('sun');
                if (dayOfWeek === 6) cellClasses.push('sat');
                if (shift.isHoliday) cellClasses.push('holiday');
                if (dateStr === todayStr) cellClasses.push('today');

                cell.className = cellClasses.join(' ');
                cell.onclick = () => openOverrideModal(dateStr, dateObj, shift);

                let badgeClass = 'off';
                if (shift.type === 'DAY') badgeClass = 'day';
                else if (shift.type === 'NIGHT') badgeClass = 'night';
                else if (shift.type === 'SPECIAL_DAY' || shift.type === 'SPECIAL_NIGHT') badgeClass = 'special';
                else if (shift.type === 'LEAVE' || shift.type === 'HALF_LEAVE') badgeClass = 'leave';
                else if (shift.type === 'NO_OT') badgeClass = 'no-ot';
                else if (shift.type === 'UNPAID_OFF') badgeClass = 'unpaid';

                let holHtml = shift.holidayName ? `<div class="holiday-name">${shift.holidayName}</div>` : '';
                let subHtml = shift.subName ? `<div class="sub-tag">${shift.subName}</div>` : '';
                
                let memoHtml = '';
                if (dayMemos[dateStr]) {
                    memoHtml = `<div class="memo-tag">📝 ${dayMemos[dateStr]}</div>`;
                }

                cell.innerHTML = `
                    <span class="day-num">${d}</span>
                    ${holHtml}
                    <div class="shift-badge ${badgeClass}">${shift.name}</div>
                    ${subHtml}
                    ${memoHtml}
                `;
                grid.appendChild(cell);
            }

            const totalCells = firstDayIndex + lastDate;
            const remaining = (7 - (totalCells % 7)) % 7;
            for (let d = 1; d <= remaining; d++) {
                const cell = document.createElement('div');
                cell.className = 'cal-day other-month';
                cell.innerHTML = `<span class="day-num">${d}</span>`;
                grid.appendChild(cell);
            }

            document.getElementById('pill-day').innerText = counts.day;
            document.getElementById('pill-night').innerText = counts.night;
            document.getElementById('pill-special').innerText = counts.special;
            document.getElementById('pill-off').innerText = counts.off;
            document.getElementById('pill-leave').innerText = counts.leave;

            updateLeaveStats();
            updateTodayCard();
        }

        function updateTodayCard() {
            const today = new Date();
            const weekNames = ['일', '월', '화', '수', '목', '금', '토'];
            const dateStr = `${today.getFullYear()}년 ${today.getMonth() + 1}월 ${today.getDate()}일 (${weekNames[today.getDay()]})`;
            document.getElementById('today-date-text').innerText = dateStr;
            document.getElementById('today-group-badge').innerText = `${currentGroup}조`;

            const shift = getActualShift(today, currentGroup);
            let icon = '☀️';
            if (shift.type === 'NIGHT' || shift.type === 'SPECIAL_NIGHT') icon = '🌙';
            else if (shift.type === 'OFF') icon = '🛌';
            else if (shift.type === 'LEAVE' || shift.type === 'HALF_LEAVE') icon = '🌴';

            document.getElementById('today-shift-badge').innerText = `${shift.name} ${icon}`;
        }

        function goToToday() {
            const today = new Date();
            currentCalDate = new Date(today.getFullYear(), today.getMonth(), 1);
            renderCalendar();
        }

        function changeMonth(delta) {
            currentCalDate.setMonth(currentCalDate.getMonth() + delta);
            renderCalendar();
        }

        function setGroup(grp) {
            currentGroup = grp;
            document.querySelectorAll('.group-btn').forEach(b => b.classList.remove('active'));
            document.getElementById(`btn-grp-${grp}`).classList.add('active');
            localStorage.setItem('shift_active_group', grp);
            renderCalendar();
            syncFromCalendar();
        }

        function calculateFiscalYearLeave(hireDateStr, targetYear) {
            if (!targetYear) targetYear = 2026;
            if (!hireDateStr) return { leave: 0, desc: "입사년월일을 입력하시면 회계일 기준 연차가 자동 계산됩니다.", isPre2017: false };

            const parts = hireDateStr.split('-');
            const hy = parseInt(parts[0], 10);
            const hm = parseInt(parts[1], 10);
            const hd = parseInt(parts[2], 10);

            const hireDate = new Date(hy, hm - 1, hd);
            const jan1Target = new Date(targetYear, 0, 1);

            if (hireDate > jan1Target) {
                return { leave: 0, desc: `입사일(${hireDateStr})이 ${targetYear}년 1월 1일 이후입니다.`, isPre2017: false };
            }

            const reformDate = new Date(2017, 4, 29);
            const isPreReform = (hireDate < reformDate);
            const tenureYears = targetYear - hy;
            let leaveDays = 0;
            let desc = "";

            if (tenureYears <= 1) {
                const monthsWorked = 12 - hm + (hd === 1 ? 1 : 0);
                leaveDays = parseFloat((15 * (monthsWorked / 12)).toFixed(1));
                const reformTag = isPreReform ? "2017.05.29 이전 입사 (기타소급 대상)" : "2017.05.29 이후 입사";
                desc = `회계연도 기준 1년차 정산: 전년도 ${monthsWorked}개월 근무 비례연차 ${leaveDays}일 [${reformTag}]`;
            } else {
                let added = Math.max(0, Math.floor((tenureYears - 3) / 2));
                leaveDays = Math.min(25, 15 + added);
                const reformTag = isPreReform ? "2017.05.29 이전 입사 (기타소급 대상)" : "2017.05.29 이후 입사";
                desc = `회계연도 기준 근속 ${tenureYears}년차 정기부여: 기본 15일 + 근속가산 ${added}일 = ${leaveDays}일 [${reformTag}]`;
            }

            const isPre2017 = (hy < 2017 || (hy === 2017 && (hm < 5 || (hm === 5 && hd <= 29))));
            return { leave: leaveDays, desc: desc, isPre2017: isPre2017 };
        }

        function onHireDateChange() {
            const hireVal = document.getElementById('input-hire-date').value;
            config.hireDate = hireVal;
            document.getElementById('input-hire-date').value = hireVal;
            document.getElementById('inp-hire-date').value = hireVal;

            const res = calculateFiscalYearLeave(hireVal, 2026);
            config.totalLeave = res.leave;
            document.getElementById('input-total-leave').value = res.leave;

            const infoBox = document.getElementById('leave-calc-info-box');
            if (infoBox) {
                infoBox.innerHTML = `📌 <strong>${res.desc}</strong>`;
            }

            config.applyRetroPay = res.isPre2017;
            document.getElementById('inp-retro-check').checked = res.isPre2017;
            updateRetroStatusText(res.isPre2017);

            saveConfig();
            updateLeaveStats();
            calculatePayrollFromInputs();
        }

        function onPayrollHireDateChange() {
            const hireVal = document.getElementById('inp-hire-date').value;
            document.getElementById('input-hire-date').value = hireVal;
            onHireDateChange();
        }

        function updateLeaveStats() {
            let used = 0;
            Object.values(overrides).forEach(val => {
                if (val === 'LEAVE') used += 1.0;
                else if (val === 'HALF_LEAVE') used += 0.5;
            });

            const total = config.totalLeave;
            const remain = Math.max(0, total - used);
            const dailyRate = config.ordinaryHourly * 8;
            const totalLeavePay = remain * dailyRate;

            document.getElementById('banner-total-leave').innerText = total;
            document.getElementById('banner-used-leave').innerText = used;
            document.getElementById('banner-remain-leave').innerText = remain;
            document.getElementById('banner-leave-pay').innerText = `${fmt(totalLeavePay)}원`;

            document.getElementById('input-total-leave').value = total;
            document.getElementById('stat-total-leave').innerText = `${total}일`;
            document.getElementById('stat-used-leave').innerText = `${used}일`;
            document.getElementById('stat-remain-leave').innerText = `${remain}일`;
            document.getElementById('val-leave-daily-rate').innerText = `${fmt(dailyRate)}원`;
            document.getElementById('val-total-leave-pay').innerText = `${fmt(totalLeavePay)}원`;
        }

        function saveLeaveConfig() {
            config.totalLeave = parseFloat(document.getElementById('input-total-leave').value) || 0;
            saveConfig();
            updateLeaveStats();
        }

        function saveWageConfig() {
            config.baseHourly = parseFloat(document.getElementById('input-base-hourly').value) || 0;
            config.ordinaryHourly = parseFloat(document.getElementById('input-ordinary-hourly').value) || 0;
            config.baseHours = parseFloat(document.getElementById('input-base-hours').value) || 209;
            config.dutyPay = parseFloat(document.getElementById('input-duty-pay').value) || 0;
            config.seniorityPay = parseFloat(document.getElementById('input-seniority-pay').value) || 0;
            saveConfig();
            updateLeaveStats();
            calculatePayrollFromInputs();
        }

        function manualSaveData() {
            saveLeaveConfig();
            saveWageConfig();
            alert("💾 모든 입력값과 설정이 안전하게 저장되었습니다!");
        }

        function openOverrideModal(dateStr, dateObj, currentShift) {
            selectedDateStr = dateStr;
            const weekNames = ['일', '월', '화', '수', '목', '금', '토'];
            document.getElementById('modal-date-text').innerText = `${dateStr} (${weekNames[dateObj.getDay()]})`;

            const base = getBaseShift(dateObj, currentGroup);
            document.getElementById('modal-orig-text').innerText = `[기본: ${base.name}${currentShift.holidayName ? ' · ' + currentShift.holidayName : ''}]`;
            
            document.getElementById('modal-memo-input').value = dayMemos[dateStr] || '';
            document.getElementById('modal-override').classList.add('active');
        }

        function closeModalDirect() {
            document.getElementById('modal-override').classList.remove('active');
        }

        function closeModal(e) {
            if (e.target.id === 'modal-override') closeModalDirect();
        }

        function onMemoInputChange() {
            if (!selectedDateStr) return;
            const val = document.getElementById('modal-memo-input').value;
            if (val.trim() === '') {
                delete dayMemos[selectedDateStr];
            } else {
                dayMemos[selectedDateStr] = val;
            }
            localStorage.setItem('shift_day_memos', JSON.stringify(dayMemos));
            renderCalendar();
        }

        function setDayOverride(type) {
            if (!selectedDateStr) return;
            if (type === null) delete overrides[selectedDateStr];
            else overrides[selectedDateStr] = type;

            saveOverrides();
            closeModalDirect();
            renderCalendar();
            syncFromCalendar();
        }

        function saveOverrides() {
            localStorage.setItem(`shift_overrides_${currentGroup}`, JSON.stringify(overrides));
        }

        function loadOverrides() {
            const saved = localStorage.getItem(`shift_overrides_${currentGroup}`);
            if (saved) {
                try { overrides = JSON.parse(saved); } catch (e) { overrides = {}; }
            } else {
                overrides = {};
            }
            const savedMemos = localStorage.getItem('shift_day_memos');
            if (savedMemos) {
                try { dayMemos = JSON.parse(savedMemos); } catch (e) { dayMemos = {}; }
            } else {
                dayMemos = {};
            }
        }

        function toggleRetroCheck() {
            const chk = document.getElementById('inp-retro-check');
            chk.checked = !chk.checked;
            config.applyRetroPay = chk.checked;
            updateRetroStatusText(chk.checked);
            saveConfig();
            calculatePayrollFromInputs();
        }

        function updateRetroStatusText(isApplied) {
            const el = document.getElementById('disp-retro-status');
            if (el) {
                if (isApplied) {
                    el.value = "적용 (17년 이전 입사)";
                    el.style.color = "#b45309";
                } else {
                    el.value = "미적용 (17년 이후 입사)";
                    el.style.color = "#64748b";
                }
            }
        }

        function changePayMonth(delta) {
            currentPayDate.setMonth(currentPayDate.getMonth() + delta);
            syncFromCalendar();
        }

        function syncFromCalendar() {
            const year = currentPayDate.getFullYear();
            const month = currentPayDate.getMonth();
            const payMonthNum = month + 1;

            document.getElementById('pay-month-title').innerText = `${year}년 ${payMonthNum}월 급여`;
            const startDate = new Date(year, month - 1, 16);
            const endDate = new Date(year, month, 15);

            const startStr = toDateKey(startDate.getFullYear(), startDate.getMonth(), startDate.getDate());
            const endStr = toDateKey(endDate.getFullYear(), endDate.getMonth(), endDate.getDate());
            document.getElementById('pay-period-label').innerText = `산정기간: ${startStr} ~ ${endStr}`;

            let E2 = 0;
            let E3 = 0;
            let E4 = 0;
            let E5 = 0;
            let noOtDays = 0;

            let curr = new Date(startDate.getTime());
            while (curr <= endDate) {
                const shift = getActualShift(curr, currentGroup);

                if (shift.type === 'DAY') {
                    E2++;
                } else if (shift.type === 'NIGHT') {
                    E3++;
                } else if (shift.type === 'SPECIAL_DAY') {
                    E4++;
                } else if (shift.type === 'SPECIAL_NIGHT') {
                    E5++;
                } else if (shift.type === 'NO_OT') {
                    if (shift.origType === 'NIGHT') E3++;
                    else E2++;
                    noOtDays++;
                }

                curr.setDate(curr.getDate() + 1);
            }

            document.getElementById('inp-day-days').value = E2;
            document.getElementById('inp-night-days').value = E3;
            document.getElementById('inp-daysp-days').value = E4;
            document.getElementById('inp-nightsp-days').value = E5;
            document.getElementById('inp-no-ot-days').value = noOtDays;

            document.getElementById('inp-bonus-check').checked = (payMonthNum % 2 === 0);

            calculatePayrollFromInputs();
        }

        function toggleBonusCheck() {
            const chk = document.getElementById('inp-bonus-check');
            chk.checked = !chk.checked;
            calculatePayrollFromInputs();
        }

        // 급여 및 상여 계산 엔진 (공제 추정치 제외)
        function calculatePayrollFromInputs() {
            const E2 = parseFloat(document.getElementById('inp-day-days').value) || 0;
            const E3 = parseFloat(document.getElementById('inp-night-days').value) || 0;
            const E4 = parseFloat(document.getElementById('inp-daysp-days').value) || 0;
            const E5 = parseFloat(document.getElementById('inp-nightsp-days').value) || 0;
            const noOtDays = parseFloat(document.getElementById('inp-no-ot-days').value) || 0;
            const holidayBonus = parseFloat(document.getElementById('inp-holiday-bonus').value) || 0;
            const hasBonus = document.getElementById('inp-bonus-check').checked;
            const applyRetro = document.getElementById('inp-retro-check').checked;

            const B7 = config.baseHourly;
            const B8 = config.ordinaryHourly;
            const baseHours = config.baseHours || 209;

            const basicPay = B7 * baseHours;
            const dutyPay = config.dutyPay;
            const seniorityPay = config.seniorityPay;

            const normalWorkDays = E2 + E3;
            const effectiveOtDays = Math.max(0, normalWorkDays - noOtDays);
            const totalOtHours = effectiveOtDays * 2.5;
            document.getElementById('disp-ot-hours').value = `${totalOtHours.toFixed(1)}h (${effectiveOtDays}일 적용)`;

            const otPay = Math.round(B8 * 1.5 * totalOtHours);
            const nightPay = Math.round(B8 * 0.5 * 7.0 * E3);
            const holPay = Math.round(B8 * 1.5 * 8.0 * (E4 + E5));
            const holOtPay = Math.round(B8 * 2.0 * 2.5 * (E4 + E5));
            const holNightPay = Math.round(B8 * 0.5 * 7.0 * E5);

            let otherPay = 0;
            if (applyRetro) {
                const diff1 = ((B8 * 1.5 * 2.5 * E2) + (B8 * 1.5 * 3 * E3)) - (B8 * 1.5 * 2.5 * (E2 + E3));
                const diff2 = ((B8 * 2 * 2.5 * E4) + (B8 * 2 * 3 * E5)) - (B8 * 2 * 2.5 * (E4 + E5));
                const diff3 = (B8 * 0.5 * 8 * E5) - (B8 * 0.5 * 7 * E5);
                const diff4 = (B8 * 0.5 * 8 * E3) - (B8 * 0.5 * 7 * E3);
                otherPay = Math.round(diff1 + diff2 + diff3 + diff4);
            }

            const regularGross = basicPay + dutyPay + seniorityPay + otPay + nightPay + holPay + holOtPay + holNightPay + otherPay + holidayBonus;

            let bonusPay = 0;
            if (hasBonus) {
                bonusPay = Math.round(basicPay * 0.5) + seniorityPay;
                document.getElementById('bonus-badge').style.display = 'inline-block';
            } else {
                document.getElementById('bonus-badge').style.display = 'none';
            }

            const grandGross = regularGross + bonusPay;

            // 상단 히어로 카드 갱신 (세전 총지급액 / 기본 수당 급여 / 상여금)
            document.getElementById('hero-gross-pay').innerText = `${fmt(grandGross)} 원`;
            document.getElementById('hero-regular-pay').innerText = `${fmt(regularGross)} 원`;
            document.getElementById('hero-bonus-pay').innerText = `${fmt(bonusPay)} 원`;

            // 지급 상세 내역 테이블 갱신
            document.getElementById('row-base-pay').innerText = fmt(basicPay);
            document.getElementById('row-duty-pay').innerText = fmt(dutyPay);
            document.getElementById('row-seniority-pay').innerText = fmt(seniorityPay);
            document.getElementById('row-ot-pay').innerText = fmt(otPay);
            document.getElementById('row-night-pay').innerText = fmt(nightPay);
            document.getElementById('row-hol-pay').innerText = fmt(holPay);
            document.getElementById('row-hol-ot-pay').innerText = fmt(holOtPay);
            document.getElementById('row-hol-night-pay').innerText = fmt(holNightPay);
            document.getElementById('row-holiday-bonus').innerText = fmt(holidayBonus);
            document.getElementById('row-other-pay').innerText = fmt(otherPay);
            document.getElementById('row-bonus-pay').innerText = fmt(bonusPay);
            document.getElementById('row-gross-pay').innerText = fmt(grandGross);
        }

        function loadConfig() {
            const saved = localStorage.getItem('shift_salary_config_v13');
            if (saved) {
                try { config = { ...config, ...JSON.parse(saved) }; } catch (e) {}
            }
            if (config.hireDate) {
                document.getElementById('input-hire-date').value = config.hireDate;
                document.getElementById('inp-hire-date').value = config.hireDate;
                const res = calculateFiscalYearLeave(config.hireDate, 2026);
                const infoBox = document.getElementById('leave-calc-info-box');
                if (infoBox) infoBox.innerHTML = `📌 <strong>${res.desc}</strong>`;
            }
            document.getElementById('input-total-leave').value = config.totalLeave;
            document.getElementById('input-base-hourly').value = config.baseHourly;
            document.getElementById('input-ordinary-hourly').value = config.ordinaryHourly;
            document.getElementById('input-base-hours').value = config.baseHours;
            document.getElementById('input-duty-pay').value = config.dutyPay;
            document.getElementById('input-seniority-pay').value = config.seniorityPay;
            document.getElementById('inp-retro-check').checked = config.applyRetroPay;
            updateRetroStatusText(config.applyRetroPay);
        }

        function saveConfig() {
            localStorage.setItem('shift_salary_config_v13', JSON.stringify(config));
        }

        function resetDefaults() {
            if (confirm('모든 설정값을 기본값(0)으로 초기화하시겠습니까?')) {
                config = {
                    hireDate: '',
                    totalLeave: 0,
                    baseHourly: 0,
                    ordinaryHourly: 0,
                    baseHours: 209,
                    dutyPay: 0,
                    seniorityPay: 0,
                    applyRetroPay: false,
                    holidayBonus: 0
                };
                localStorage.removeItem('shift_salary_config_v13');
                localStorage.removeItem('shift_day_memos');
                dayMemos = {};
                loadConfig();
                const infoBox = document.getElementById('leave-calc-info-box');
                if (infoBox) infoBox.innerHTML = "📅 <strong>회계연도 기준(매년 1월 1일 정산):</strong> 입사년월일을 입력하시면 회계일 기준 연차가 자동으로 산출됩니다.";
                updateLeaveStats();
                syncFromCalendar();
                renderCalendar();
                alert("🔄 초기화되었습니다.");
            }
        }

        function switchView(viewName) {
            document.querySelectorAll('.view-page').forEach(el => el.classList.remove('active'));
            document.querySelectorAll('.main-tab-btn').forEach(el => el.classList.remove('active'));

            document.getElementById(`view-${viewName}`).classList.add('active');

            if (viewName === 'calendar') {
                document.getElementById('tab-btn-cal').classList.add('active');
                renderCalendar();
            } else if (viewName === 'payroll') {
                document.getElementById('tab-btn-pay').classList.add('active');
                syncFromCalendar();
            } else if (viewName === 'leave') {
                document.getElementById('tab-btn-leave').classList.add('active');
                updateLeaveStats();
            }
            window.scrollTo({ top: 0, behavior: 'smooth' });
        }

        window.onload = function() {
            const savedGroup = localStorage.getItem('shift_active_group');
            if (savedGroup && ['A', 'B', 'C'].includes(savedGroup)) {
                currentGroup = savedGroup;
                document.querySelectorAll('.group-btn').forEach(b => b.classList.remove('active'));
                document.getElementById(`btn-grp-${savedGroup}`).classList.add('active');
            }

            loadConfig();
            loadOverrides();
            renderCalendar();
            syncFromCalendar();
        };
    </script>
</body>
</html>
