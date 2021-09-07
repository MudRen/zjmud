// due.c

inherit NPC;
inherit F_MASTER;

mixed ask_me();

void create()
{
	set_name("�ɶ�", ({ "du e", "e" }) );
	set("title", "���ֳ���");
	set("gender", "����");
	set("age", 90);
	set("long",
		"����һ��������ݣ��ݹ��㶡����ɮ������ɫ"
		"�ݻƣ���ͬһ�ο�ľ��\n");

	set("attitude", "peaceful");
	set("class", "bonze");
	set("combat_exp", 2350000);

	set("str", 34);
	set("int", 36);
	set("con", 35);
	set("dex", 33);

	set("qi", 5800);
	set("max_qi", 2900);
	set("neili", 7200);
	set("max_neili", 7200);
	set("jiali", 110);

	create_family("������", 35, "����");
	assign_apprentice("����", 0);

	set_skill("buddhism", 250);
	set_skill("force", 270);
	set_skill("whip", 270);
	set_skill("parry", 270);
	set_skill("dodge", 260);

	set_skill("hunyuan-yiqi", 270);
	set_skill("shaolin-xinfa", 270);
	set_skill("riyue-bian", 270);
	set_skill("shaolin-shenfa", 260);

	map_skill("force", "hunyuan-yiqi");
	map_skill("whip",  "riyue-bian");
	map_skill("parry", "riyue-bian");
	map_skill("dodge", "shaolin-shenfa");

	set_skill("finger", 260);
	set_skill("strike", 260);
	set_skill("nianhua-zhi", 260);
	set_skill("sanhua-zhang", 260);

	map_skill("finger", "nianhua-zhi");
	map_skill("strike", "sanhua-zhang");

	prepare_skill("finger", "nianhua-zhi");
	prepare_skill("strike", "sanhua-zhang");

	set_skill("medical", 250);
	set_skill("shaolin-yishu", 250);

	set("inquiry", ([
		"��ħ��"     : (: ask_me :),
	]));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
		(: perform_action, "finger.fuxue" :),
		(: perform_action, "strike.san" :),
		(: perform_action, "whip.chan" :),
		(: perform_action, "whip.he" :),
		(: perform_action, "whip.shang" :),
	}));

	setup();
}

mixed ask_me()
{
	mapping fam; 
	object ob;
	object me;
	
	me = this_player();
	if (! me->query_temp("valid_in_fumoquan"))
	{
		command("say ���󱲣����δ�ɣ�����͵���շ�ħȦ�������������������㣡");
		kill_ob(me);
		return 1;
	}

	if (me->query_temp("valid_in_fumoquan") != 1)
	{
		command("heng");
		return 1;
	}

	if (me->query("combat_exp") < 1000000)
		return "�����΢ĩ���£�������Ħ��ʦ���µ�����������";

	if (present("fumo zhang", me))
		return RANK_D->query_respect(me) + 
		"����ֻ��һ�ѣ����Ҿ��������ϣ�����̰�����У�";

	if (present("fumo zhang", environment()) )
		return RANK_D->query_respect(me) + 
		"����ֻ��һ�ѣ����Ҿ�����������ȡ�ߣ�����̰�����У�";

	ob = get_object("/d/shaolin/obj/fumo-zhang");
	if (! ob || environment(ob) && environment(ob) != this_object())
		return "��Ǹ���������ˣ���ħ���Ѿ�����ȡ���ˡ�";

	message_vision("$N��Цһ�������ͷ��������������ȡ����ħ�Ƚ���$n��\n",
		       this_object(), me);
	ob->move(me, 1);

	return "���Ȼ�ܴ�����շ�ħȦ������Ȼ�ǵ��������еķǷ�������ħ�����ʷ������ˣ�";
}

#include "/kungfu/class/shaolin/du.h"
