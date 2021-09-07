// wgargoyle.c
#include <ansi.h>
#include <command.h>
#include <login.h>
inherit NPC;
inherit F_DEALER;
int ask_me();

string *death_msg = ({
	HIW "���޳�˵����ι�������ģ����ʲô���֣�"NOR"\n",
	HIW "���޳���������۹ⶢ���㣬����Ҫ�������һ���Ƶġ�"NOR"\n",
	HIW "���޳����ߡ���һ�����������ͳ�һ�����ʲ�Ķ�����������"NOR"\n",
	HIW "���޳����ϲ��ӣ�˵�����ף�����δ������ô���ܣ�"NOR"\n",
	HIW "���޳�ɦ��ɦͷ��̾�������˰��ˣ����߰ɡ�\n"
		"һ�������Ũ��ͻȻ���֣��ܿ�ذ�Χ���㡣"NOR"\n",
});
void create()
{
	set_name("���޳�", ({ "w gargoyle","white", "gargoyle" }) );
	set("title", "��ʹ");
	set("long","���޳�������������ͷ�����㣬���׵����Ͽ������κ�ϲŭ���֡�\n");
	set("attitude", "peaceful");
	set("chat_chance", 15);
	set("chat_msg", ({
		"���޳�����һ����������������������������ע��������ʱ�򣬵�����һ�ۡ�\n",
		"���޳��ѳ�������ͷ��������������������Լ��ְ��ֳ�����ָ��\n",
	}) );
	set("age", 217);
	set("no_die",1);
	set("icon","00165");
	set("combat_exp", 20000);
	set("max_jing", 900);
	set("max_qi", 900);
	set_skill("dodge", 80);
	set_skill("unarmed", 80);
	set("inquiry", ([
		"��ħ����" : (: ask_me :),
	]));
	setup();
}
void init()
{
	::init();
	call_out( "death_stage", 10,this_player(), 0 );
}
void death_stage(object ob, int stage)
{
	int i;
	object *inv,me;
	me = this_player();
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
	if (!mapp(my_fam)||my_fam["family_name"] != "ؤ��")
		return notify_fail("�㲻��ؤ��ĵ��ӣ�������ħ���塣\n");
	if( already_age >= my_age)
		return notify_fail("��������ħ��������Ѿ������ˣ�\n");
	if( (int)me->query("max_neili") < 50)
		return notify_fail("����������������ħ����󷨣�\n");
	if(random(5) >= 2)
	{
		me->set_skill("force",me->query_skill("force",1)+5);
		me->add("con_improve_time", 1);
		me->add("max_neili", -50);
		me->set("already_age", my_age);
		message_vision(HIY"ֻ�����޳��������еĿ�ɥ�����૵����˼��������ڵ������ͻȻ��"
					"��һ�����磬�������ͷ������ֻ���û������Ǳ�������һ��ů���С�������������ˣ�"NOR"\n", me);
	}
	else
		message_vision(HIY"ֻ�����޳��������еĿ�ɥ�����૵����˼���������ʲôҲû������"NOR"\n", me);
	return 1;
	
}
