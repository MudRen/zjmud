// liandan_tongzi.c

#include <ansi.h>

inherit NPC;

mixed ask_caiyao();

void create()
{
	set_name("Сͯ", ({"xiao tong", "xiao", "tong"}));
	set("gender", "����");
	set("age", 12);
	set("long",
		"�����������е��ƹ�ҩ�ĵ�ͯ�ӡ�����Ͳ��󣬵��������Ե������ϳɡ�\n");
	set("attitude", "friendly");
	set("shen_type",1);
	set("str", 21);
	set("int", 22);
	set("con", 23);
	set("dex", 22);
	set("qi", 600);
	set("max_qi", 600);
	set("jing", 400);
	set("max_jing", 400);
	set("neili", 1200);
	set("max_neili", 1200);;

	set("combat_exp", 300000);

	set("inquiry", ([
		"��ҩ" : (: ask_caiyao :),
	]) );
	set("caiyao", 12);

	setup();
}

mixed ask_caiyao()
{
        int k;
	object me = this_player();

	switch (me->query_temp("caiyao"))
	{
	case 1:
		return "����ȥ��ҩ������������";

	case 2:
		return "ҩ�����ˣ���������ң�";
	}

	switch (me->query_temp("liandan"))
	{
	case 1:
		// �Ѿ�����������������Ϣ��
		break;

	case 2:
		return "ҩ���Ѿ�׼���ã�����ȥ�ˡ�";

	case 3:
		return "�㲻����������ҩ����ô�����ˡ�";

	case 4:
		return "������ȥ�����ɡ�";

	default:
		return "���ֲ���ҩ��Ҫҩ�ĸ�ʲô��";
	}

	message_vision(CYN "Сͯ��$N" CYN "˵�����ðɣ�����ȥ�������������ڼ������ʵĲ�ҩ����"NOR"\n", me);
	me->set_temp("caiyao", 1);
	add("caiyao", -1);
	if(objectp(present("cao yao",me))) {

            call_out("do_lian1", 5, me);
           }
      else {
            me->move("/d/beijing/ximenwai");
            tell_object(me,ZJFORCECMD("n")+ZJFORCECMD("cai yao"));
           }
/*
k=random(8);
if (k==0) tell_object(me,ZJFORCECMD("s"));
else if (k==1) tell_object(me,ZJFORCECMD("s")+ZJFORCECMD("w"));
else if (k==2) tell_object(me,ZJFORCECMD("s")+ZJFORCECMD("s"));
else if (k==3) tell_object(me,ZJFORCECMD("s")+ZJFORCECMD("e"));
else if (k==4) tell_object(me,ZJFORCECMD("n"));
else if (k==5) tell_object(me,ZJFORCECMD("n")+ZJFORCECMD("w"));
else if (k==6) tell_object(me,ZJFORCECMD("n")+ZJFORCECMD("n"));
else if (k==7) tell_object(me,ZJFORCECMD("n")+ZJFORCECMD("e"));
tell_object(me,ZJFORCECMD("cai yao"));
*/
	return 1;
}

int accept_object(object me, object ob)
{
	int exp,pot;

	if (me->query_temp("caiyao") < 1)
		command("say ��ʲôʱ�������������ҵģ�");
	else
	if (me->query_temp("caiyao") == 1)
		command("say ��˭�����ҵĶ����������ң�����Ϊ��С�ͺ�ƭ��");
	else
	if (ob->query("id") != "cao yao")
		command("say ������С���������ֶ���ƭ�ҡ�");
	else
	{
		command("say �ðɣ�����������ӹ���"NOR"\n");
		destruct(ob);
	      call_out("do_lian3", 5, me);
            return 1;
	}
}

void do_lian1(object me)
{
	if (! objectp(me))
		return;
            write("�㷭�˷��ڴ������÷����м��겻֪����ҩ��"NOR"\n");
		//command("say �ӹ����ˣ����������ȥ���������ˡ�");
		me->set_temp("caiyao", 2);

            tell_object(me,ZJFORCECMD("give 1 cao yao to xiao tong"));

}
void do_lian3(object me)
{
	if (! objectp(me))
		return;

		command("say ��ҩ�Ѿ��ӹ����ˣ����������ȥ���������ˡ�");
		me->delete_temp("caiyao");
		me->set_temp("liandan", 2);

            tell_object(me,ZJFORCECMD("n")+ZJFORCECMD("n")+ZJFORCECMD("liandan"));

}
