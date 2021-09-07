inherit NPC;
#include <ansi.h>

void create()
{
	set_name("����", ({ "ao bai", "ao", "bai" }));
	set("age", 32);
	set("gender", "����");
	set("title", "������һ��");
	set("nickname", HIR "���޵�һ��ʿ" NOR );
	set("long",
		"���������޵�һ��ʿ����һ������ӡ�����Ŀ��࣬\n"
		"��ò������̫��Ѩ�߸߹����ƺ��������书��\n");
	set("attitude", "peaceful");

	set("age", 50);
	set("shen_type", -1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("max_qi", 1500);
	set("max_jing", 1500);
	set("neili", 1500);
	set("max_neili", 1500);
	set("jiali", 100);
	set("combat_exp", 150000);
	set("score", 50000);

	set_skill("unarmed", 120);
	set_skill("dodge", 120);
	set_skill("parry", 120);
	set_skill("sword", 120);
	set_skill("force", 120);
	set_skill("huashan-sword", 120);
	set_skill("shaolin-shenfa", 120);
	set_skill("literate", 100);

	map_skill("dodge", "shaolin-shenfa");
	map_skill("parry", "huashan-sword");
	map_skill("sword", "huashan-sword");

	setup();
	carry_object(__DIR__"obj/goldcloth1")->wear();
}

int accept_fight(object me)
{
	command("say �����̵ģ�������ˣ����ˣ��������£�\n");
	me->apply_condition("killer", 500);
	kill_ob(me);
	return 1;
}
