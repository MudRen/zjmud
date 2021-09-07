// bgargoyle.c
#include <ansi.h>
#include <command.h>
#include <login.h>
inherit NPC;
inherit F_DEALER;
int ask_me();
string *death_msg = ({
	HIB "���޳�˵����ι�������ģ����ʲô���֣�"NOR"\n",
	HIB "���޳���������۹ⶢ���㣬����Ҫ�������һ���Ƶġ�"NOR"\n",
	HIB "���޳����ߡ���һ�����������ͳ�һ�����ʲ�Ķ�����������"NOR"\n",
	HIB "���޳����ϲ��ӣ�˵�����ף�����δ������ô���ܣ�"NOR"\n",
	HIB "���޳�ɦ��ɦͷ��̾�������˰��ˣ����߰ɡ�\n"
		"һ�������Ũ��ͻȻ���֣��ܿ�ذ�Χ���㡣"NOR"\n",
});
void create()
{
	set_name("���޳�", ({ "b gargoyle", "gargoyle","black" }) );
	set("title", "��ʹ");
	set("long",
		"���޳�������������ͷ�����㣬��ڵ����Ͽ������κ�ϲŭ���֡�\n");
	set("attitude", "peaceful");
	set("chat_chance", 15);
	set("chat_msg", ({
		"���޳�����һ����������������������������ע��������ʱ�򣬵�����һ�ۡ�\n",
		"���޳��ѳ�������ͷ��������������������Լ��ֺ��ֳ�����ָ��\n"
	}) );
	set("age", 217);
	set("combat_exp", 20000);
	set("max_jing", 900);
	set("icon","00321");
	set("max_qi", 900);
	set_skill("dodge", 80);
	set_skill("unarmed", 80);
	set_temp("apply/armor", 60);
	set_temp("apply/damage", 20);
	set("no_die",1);		//������ɱ��������.
	set("inquiry", ([
		"��ɲ����" : (: ask_me :),
	]));
	setup();
}
void init()
{
	::init();
	if( !previous_object()||!userp(previous_object()) )
		return;
	call_out( "death_stage", 10, previous_object(), 0 );
}
void death_stage(object ob, int stage)
{
	int i;
	object *inv;
	if( !ob || !present(ob,environment()) ) return;
	if( !ob->is_ghost() ) {
		command("say ι��������������ʲô��");
		kill_ob(ob);
		ob->fight_ob(this_object());
		return;
	}
	tell_object(ob, death_msg[stage]);
	if( ++stage < sizeof(death_msg) ) {
		call_out( "death_stage", 5, ob, stage );
		return;
	} else
		ob->reincarnate();
	
	ob->move("/d/city/wumiao");
	ob->set("startroom","/d/city/wumiao");
	message("vision","���Ȼ����ǰ�����һ����Ӱ����������Ӱ�ֺ����Ѿ�������ܾ��ˣ�ֻ����һֱû������\n", environment(ob), ob);
}
int ask_me()
{
	mapping my_fam;
 
	object  me;
	int my_age, already_age;
	me = this_player();
	my_fam = (mapping)me->query("family");
	my_age = me->query("age");
	already_age = (int)me->query("already_age");
	if (!mapp(my_fam)||my_fam["family_name"] != "������")
		return notify_fail("�㲻�������ɵĵ��ӣ����ܵ�ɲ���ꡣ\n");
	if( already_age >= my_age)
		return notify_fail("�����ĵ�ɲ��������Ѿ������ˣ�\n");
	if( (int)me->query("max_neili") < 50)
		return notify_fail("�������������ɵ�ɲ����󷨣�\n");
	if(random(5) >= 2)
	{
		me->set_skill("force",me->query_skill("force",1)+5);
		me->add("con_improve_time", 1);
		me->add("max_neili", -50);
		me->set("already_age", my_age);
		message("vision", HIY"ֻ�����޳��������еĿ�ɥ�����૵����˼��������ڵ������ͻȻ��"
					"��һ�����磬�������ͷ������ֻ���û������Ǳ�������һ��ů���С�������������ˣ�"NOR"\n", me);
	}
	else
		message("vision", HIY"ֻ�����޳��������еĿ�ɥ�����૵����˼���������ʲôҲû������"NOR"\n", me);
	return 1;
	
}
