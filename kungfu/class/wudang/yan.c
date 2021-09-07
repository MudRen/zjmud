// yan.c �����

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("�����", ({ "yu daiyan", "yu" }));  
	set("nickname","�䵱����");
	set("long", 
		"�����������������������ҡ�\n"
		"��һ���ɸɾ����Ļ�ɫ���ۡ�\n"
		"���������ʮ������ݳ����񵭳�ͣ���Ĭ���ԡ�\n");
	set("gender", "����");
	set("age",43);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 29);
	set("int", 28);
	set("con", 31);
	set("dex", 25);
	
	set("max_qi", 4400);
	set("max_jing", 2000);
	set("neili", 5200);
	set("max_neili", 5200);
	set("jiali", 100);
	set("combat_exp", 1450000);
	set("score", 45000);

	set_skill("force", 190);
	set_skill("wudang-xinfa", 190);
	set_skill("taiji-shengong", 190);
	set_skill("dodge", 165);
	set_skill("tiyunzong", 165);
	set_skill("unarmed", 170);
	set_skill("taiji-quan", 170);
	set_skill("strike", 170);
	set_skill("wudang-zhang", 170);
	set_skill("hand", 170);
	set_skill("paiyun-shou", 170);
	set_skill("parry", 175);
	set_skill("sword", 180);
	set_skill("wudang-jian", 180);
	set_skill("taiji-jian", 180);
  	set_skill("taoism", 160);
	set_skill("literate", 100);

	set("no_teach", ([
		"taiji-shengong" : "Ҫ��ѧϰ̫����������������̡�",
		"taiji-jian"     : "̫���������������״���",
		"taiji-quan"     : "̫��ȭ�����������״���",
	]));

	map_skill("force", "taiji-shengong");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-quan");
	map_skill("sword", "taiji-jian");
	map_skill("strike", "wudang-zhang");

	prepare_skill("unarmed", "taiji-quan");
	prepare_skill("strike", "wudang-zhang");

	create_family("�䵱��", 2, "����");
	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/greyrobe")->wear();

}

void init()
{
	object ob;

	::init();
	if (interactive(ob = this_player()) && ! is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 2, ob);
	}
}

void greeting(object ob)
{
	int i;

	if (! objectp(ob) || environment(ob) != environment())
		return;

	if ((int)ob->query_skill("wudang-xinfa", 1) == 0)
	{
		message_vision(CYN "ʮ�����Ӷ�$N" CYN "�����ȵ�������"
			       "��аħ������������佣��"NOR"\n", ob);
		ob->set("qi", 30);

		if ((int)ob->query("combat_exp") < 2000)
			ob->set("combat_exp", 1);
		else    ob->add("combat_exp", -1000);

		message_vision(CYN "���佣���ʱ��������̨�Ͻ����ݺᣬ��$N" CYN "Χ�����롣"NOR"\n", ob);
		message_vision(CYN "ʮ���ڳ����������$N" CYN "���ϻ�����ʮ�������ӣ���Ѫ���졣"NOR"\n", ob);
		say(CYN "\n\n���������ŭ�ݣ���аħ�����Ҳ�Ҵ����佣�󣡡�\n");
		message_vision("����ҾӸ����£�����һ�ư�$N�����̨��\n"NOR"\n", ob);
		ob->move("/d/wudang/nanyangong");
		CHANNEL_D->do_channel(this_object(), "chat",
				      sprintf("%s˽�����佣������"
					      "�ɳ����ף�����һ����", ob->name(1)));
	}
}

void attempt_apprentice(object me)
{
	if (! permit_recruit(me))
		return;

	if ((int)me->query_skill("wudang-xinfa", 1) < 30)
	{
		command("say ���䵱�����ڼ��书���������ڹ��ķ���");
		command("say " + RANK_D->query_respect(me) +
			"�Ƿ�Ӧ����̫�����϶��µ㹦��");
		return;
	}

	if ((int)me->query("shen") < 10000)
	{
		command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(me) +
			"�Ƿ����ò�����");
		return;
	}

	if ((int)me->query_skill("wudang-xinfa", 1) < 70)
	{
		command("say ���䵱����ע���ڹ��ķ�" + RANK_D->query_respect(me)+
			"�Ƿ�Ӧ�����䵱�ķ��϶��µ㹦��?");
		return;
	}

	if ((int)me->query_skill("taoism", 1) < 70)
	{
		command("say ϰ����Ϊ��ǿ���壬һζ�������ǲ���ȡ�ģ�");
		command("say �ҿ��㻹��Ҫ���������Է�����������������"
			"����ĵ����ķ���");
		return;
	}

	command("say �ðɣ��Ҿ��������ˡ�");
	command("recruit " + me->query("id"));
}

void unconcious()
{
	die();
}
