//zhuangjia.c

#include <ansi.h>

inherit NPC;

object room = 0;

void create()
{
	set_name( "ׯ��", ({ "zhuang jia", "zhuang" }) );
	set("long", "���ǳ����ĳ���ְҵ��ͽ�������ϵĹ�������뻯��\n");
	set("attitude", "friendly");
	set("title", HIR "����ʥ��" NOR);
	set("force_factor", 30);
	set("max_kee", 3000);
	set("max_sen", 3000);
	set("eff_gin", 3000);
	set("eff_kee", 3000);
	set("eff_sen", 3000);
	set("kee", 3000);
	set("sen", 3000);
	set("max_force", 3000);
	set("force", 3000);
	set("max_mana", 3000);
	set("mana", 3000);
	set("age", 47);
	set_temp("apply/damage",600);
	set("gender", "����" );
	set("str", 40);
	set("cor", 35);
	set("cps", 30);
	set("per",10);
	set("max_force",3000);
	set("force_factor",40);
	set_skill("parry",170);
	set_skill("unarmed",170);
	set_skill("force",170);
	set_skill("dodge",170);
	set("combat_exp", 300000);

	setup();
	carry_object(__DIR__"obj/choupao")->wear();
}

void greeting(object ob)
{
	if (! ob || environment(ob) != environment())
		return;
	switch(random(3))
	{
	case 0:
		say("ׯ��Ц�����˵������λ" + RANK_D->query_respect(ob) +
		    "�����������֣�����������Σ�\n");
		break;
	case 1:
		say("ׯ�һ��˻����е����ӣ��е�����λ" +
		    RANK_D->query_respect(ob) +
		    "������ԥ�ˡ�����һע�ɣ�\n");
		break;
	case 2:
		say("ׯ��˵������λ" + RANK_D->query_respect(ob) +
		    "�������������� ��Ѻһ�ѣ�\n");
		break;
	}
}
