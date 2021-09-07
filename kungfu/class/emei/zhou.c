// zhou.c ������

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT; 

#include <command.h>
#include <ansi.h>
#include "emei.h"

string no_teach_jybgz();

void create()
{
	set_name("������", ({ "zhou zhiruo","zhiruo","zhou"}));
	set("long",
		"���Ƕ����ɵĵ��Ĵ����ŵ��ӡ�\n"
		"һ�����������ס�����һ�������ѡ�\n"
		"�����������Ц�д���Щ�����Ρ�\n"
		"���ܼ�į��\n");
	set("gender", "Ů��");
	set("age", 20);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "claw.duo" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}) );
	set("inquiry",([
		"���"    : "������ȣ����԰ɡ�",
		"����"    : "Ҫ�������ҵ�ʦ����ȥ��",
		"����"    : "���ġ�����Ҳ���ң�",
		"���޼�"  : "������Ķ����ļһ����Ҳ��Ҫ������",
		"����"    : "��Ҫ���������ӣ�",
		"���콣"  : "���첻����˭�����棿����",
		"������"  : "�������ֳ��ۣ��������ˡ�",
		"���ʦ̫"  : "ʦ���ѵ���ͽ�����Ȱͽ��Ұɡ�",
	]));
	set("str", 22);
	set("int", 32);
	set("con", 26);
	set("dex", 24);

	set("max_qi", 5800);
	set("max_jing", 1900);
	set("neili", 4400);
	set("max_neili", 4400);
	set("jingli", 1200);
	set("max_jingli", 1200);

	set("combat_exp", 2000000);
	set_skill("persuading", 120);
	set_skill("force", 170);
	set_skill("throwing", 150);
	set_skill("dodge", 170);
	set_skill("finger", 140);
	set_skill("parry", 170);
	set_skill("unarmed", 130);
	set_skill("strike", 145);
	set_skill("sword", 170);
	set_skill("claw", 270);
	set_skill("literate", 120);
	set_skill("mahayana", 140);
	set_skill("jinding-zhang", 145);
	set_skill("jiuyin-baiguzhao", 270);
	set_skill("tiangang-zhi", 140);
	set_skill("huifeng-jian", 170);
	set_skill("zhutian-bu", 150);
	set_skill("emei-xinfa", 170);
	set_skill("linji-zhuang", 170);
	set_skill("martial-cognize", 200);

	map_skill("force","linji-zhuang");
	map_skill("claw","jiuyin-baiguzhao");
	map_skill("dodge","zhutian-bu");
	map_skill("strike","jinding-zhang");
	map_skill("sword","huifeng-jian");
	map_skill("parry","huifeng-jian");
	create_family("������", 4, "���ŵ���");

	set("no_teach", ([
		"linji-zhuang" : "��ѧ�ټ�ʮ��ׯ�������ʦ̫ȥ��",
		"jiuyin-baiguzhao" : (: no_teach_jybgz :),
	]));

	setup();
	carry_object("/d/emei/obj/ycloth.c")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query_int() < 30)
	{
		command("say ��λ" + RANK_D->query_respect(ob) + "�������ʲ���һ�㡣");
		command("say �����д���Ǳ���������Ȼ�ȥĥ��ĥ����");
		return;
	}

	command("say " + ob->query("name") + "������ô��������Ϊ����������ɡ�\n");
	command("recruit " + ob->query("id"));
}

int recognize_apprentice(object me, string skill)
{
	if (me->query("family/family_name") != query("family/family_name"))
	{
		command("say ���ҹ���һ��ȥ��");
		return -1;
	}

	if (skill == "claw")
	{
		if (! me->query_temp("can_learn/zhou"))
		{
			command("say �ߺߣ�צ�����������е��ĵã����Ȼ��Ȥ���Ҿ�ָ��ָ������ˡ�");
			me->set_temp("can_learn/zhou", 1);
		}

		return 1;
	}

	command("say ����ʦ��ѧȥ�ɣ������ҡ�");
	return -1;
}

string no_teach_jybgz()
{
	object me;

	me = this_player();
	if (me->query("shen") < 20000)
		return "�����ˣ������������������̫�٣������ܷ��Ľ������ֺ������书��";

	return 0;
}
