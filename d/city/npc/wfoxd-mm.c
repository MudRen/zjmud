#include <ansi.h> 

inherit NPC;

void create()
{
	set_name("ӭ��С��", ({ "yinbing xiaojie", "xiaojie", "yinbing" }) );
	set("long", "����һλ������ӭ��С�㣬���������������Ц�ء�\n");
	set("title", HIR "��������־��" HIW "�칫��" NOR); 
	set("gender", "Ů��");
 
	set("age", 21);
	set("per", 30);
	setup();
	carry_object("/d/city/npc/obj/qunzi")->wear();
}

void init()
{       
	object ob; 
	mapping myfam; 

	ob = this_player();

	::init();
	if( interactive(ob) && !is_fighting() ) {
			remove_call_out("greeting");
			call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(2) ) {
		case 0:
			say( "ӭ��С��Ц�����˵������λ" + RANK_D->query_respect(ob)
				+ "����ӭ���١�\n");
			break;
		case 1:
			say( "ӭ��С�������˵������λ" + RANK_D->query_respect(ob)
				+ "����������\n");
			break;
	}
}


