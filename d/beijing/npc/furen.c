// furen.c
inherit NPC;
#include <ansi.h>

void create()
{
	set_name("ׯ����", ({ "san furen", "san","furen"}));
	set("title", "ׯ����������" );
	set("nickname", HIW "δ����" NOR);
	set("long",  "\nֻ����ԼĪ��ʮ�������,ȫ������,��ʩ֬��,��ɫ�԰�.\n");
	set("gender", "Ů��");
	set("age", 25);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 30);
	
	set("max_qi", 1000);
	set("max_jing", 400);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 100);
	set("combat_exp", 100000);
	set("score", 50000);

	set_skill("force", 90);
	set_skill("dodge", 90);
	set_skill("unarmed", 90);
	set_skill("sword", 90);
	set_skill("taiji-jian", 80);
	set_skill("tiyunzong",90);
	map_skill("dodge", "tiyunzong");
	map_skill("parry", "tiaji-jian");
	map_skill("sword", "tiaji-jian");

	set_temp("apply/attack", 35);
	set_temp("apply/attack", 35);
	set_temp("apply/damage", 35);
	set("inquiry", ([
		"����"  : "�������ҼҵĴ���ˡ�",
		"��֮��": "��һ��Ҫ���������������",
		"����"  : "��������ɲ�һ�㣬�������ҵĺ�Ѿ��˫����",
		"˫��"  : "��СѾͷ�����Ҷ��꣬����Ҳ���׵���",
	]) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
	object ob; 
	ob = this_player();

	if( interactive(ob) && !is_fighting() ) 
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if (! ob || environment(ob) != environment() || ! living(ob))
		return;

	say( "ׯ����˵�����ܾ�û�������ˣ���λ" + RANK_D->query_respect(ob) +
	     "����֪�����๫��������\n");
}

int accept_object(object me, object ob)
{
	int i;

	if ( userp(ob) ) return 0; 
	if ( (string)ob->query("id") == "wu zhi rong") 
	{
		i = (int)me->query("weiwang");

		message_vision("\nׯ���˴�ϲ������������ȥ�ɣ�"
			       "�벻����Ҳ�н��죡\n", me);
		ob->move(environment());
		ob->die();

		if ( i >= 50 && i < 70 )
		{
			i += 10;
			me->set("weiwang", i);
			message_vision(HIC "\n$N�Ľ�����������ˣ�"NOR"\n", me);
			return -1;
		}

	 	message_vision("\nׯ���˶�$N˵������λ" +
			       RANK_D->query_respect(me) +
			       "����˴����£����ʵ��֪����Ϊ����\n"
	 		       "ׯ����΢һ��˼�����������Ͷ���һ�����"
			       "������ȴ���ҡ�\n", me);
	} else
	if ( (string)ob->query("name") == "��ʷ����" || 
	     (string)ob->query("name") == "ׯ�ʳ�" )
	{
	 	message_vision("\nׯ����˵������λ" +
			       RANK_D->query_respect(me)+"����л�ˣ�\n", me);

	 	message_vision("ׯ���˸�̾����������Ҫ�ܰ����ҵ���֮����"
			       "�����ͺ��ˡ�\n", me);
	}		
 	return 1;
}

