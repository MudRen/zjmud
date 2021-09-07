// dujie.c

inherit NPC;
inherit F_MASTER;

mixed ask_me();

void create()
{
	set_name("�ɽ�", ({ "du jie", "jie" }) );
	set("title", "���ֳ���");
	set("gender", "����");
	set("age", 90);
	set("long",
		"����һ��������ݣ��ݹ��㶡����ɮ������ɫ�Ұף���һ��ֽһ����\n");

	set("attitude", "peaceful");
	set("class", "bonze");
	set("combat_exp", 2300000);

	set("str", 32);
	set("int", 30);
	set("con", 33);
	set("dex", 31);

	set("qi", 5000);
	set("max_qi", 2500);
	set("neili", 6700);
	set("max_neili", 6700);
	set("jiali", 90);

	create_family("������", 35, "����");
	assign_apprentice("����", 0);

	set_skill("buddhism", 250);
	set_skill("force", 255);
	set_skill("whip", 255);
	set_skill("parry", 250);
	set_skill("dodge", 240);

	set_skill("hunyuan-yiqi", 255);
	set_skill("shaolin-xinfa", 255);
	set_skill("riyue-bian", 255);
	set_skill("shaolin-shenfa", 240);

	map_skill("force", "hunyuan-yiqi");
	map_skill("whip",  "riyue-bian");
	map_skill("parry", "riyue-bian");
	map_skill("dodge", "shaolin-shenfa");

	set_skill("finger", 250);
	set_skill("jingang-zhi", 250);

	map_skill("finger", "jinggang-zhi");

	prepare_skill("finger", "jingang-zhi");

	set_skill("medical", 200);
	set_skill("shaolin-yishu", 200);

	set("inquiry", ([
		"�����"     : (: ask_me :),
	]));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
		(: perform_action, "finger.fumo" :),
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
		return "�����΢ĩ���£�������Ħ��ʦ���µı���������";

	if (present("jingang zhao", me))
		return RANK_D->query_respect(me) + 
		"����ֻ��һ�������Ҿ��������ϣ�����̰�����У�";

	if (present("jingang zhao", environment()))
		return RANK_D->query_respect(me) + 
		"����ֻ��һ�������Ҿ�����������ȡ�ߣ�����̰�����У�";

	ob = get_object("/d/shaolin/obj/jingang-zhao");
	if (! ob || environment(ob) && environment(ob) != this_object())
		return "��Ǹ���������ˣ�������Ѿ�����ȡ���ˡ�";

	message_vision("$Nһ�����Ե�����$N���ã�Ť������������ȡ������ֵݸ�$n��\n",
		       this_object(), me);
	ob->move(me, 1);

	return "���ܰ����������ϲ���������������޲�����ȷʵ�������������־�������ˣ�";
}

#include "/kungfu/class/shaolin/du.h"
