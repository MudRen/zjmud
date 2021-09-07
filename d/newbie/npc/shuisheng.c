// shuisheng ˮ��
#include <ansi.h>
inherit NPC;

void greeting(object me);

void create()
{
	set_name("ˮ��", ({ "shui sheng","shuisheng"}));
	set("long", "����ױ��Ĩ��üĿ֮�������͸¶��˼��\n");
	set("gender", "Ů��");
	set("age", 22);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("per", 25);

	setup();
	carry_object("/clone/cloth/cloth.c")->wear();
}

void init()
{
	object me;

	::init();
	me = this_player();
	if (! objectp(me) || ! userp(me))
		return;

	remove_call_out("greeting");
	call_out("greeting", 0, me);
}

void greeting(object me)
{
	object cloth;

	if (! objectp(me) || environment(me) != environment(this_object()))
		return;

	if (! stringp(me->query("character")))
	{
		command("tell " + me->query("id") + " ��ӭ��������Ⱥ�����磬������Ϸ�����˽Ӵ����������м��·����ȴ����ϰɣ��������ӳ�ȥ�ɲ�̫�ÿ���");
		cloth = new("/clone/cloth/cloth");
		cloth->move(me);
		tell_object(me,"��õ���һ�����¡�\n");
		command("tell " + me->query("id") + " �㻹û��ѡ��Ʒ�ʣ���ȥ�����Ĵ�����ѡѡ�ɡ��뿪ǰ�ǵ��ȰѲ��´���Ŷ��");
		tell_object(me,"�������񣺵��"HIG"������ָ�"NOR"--ѡ�񡾲鿴������--��������¡����д�����\n");
		return;
	}

	if (! wizardp(me))
	{
		command("tell " + me->query("id") + " �ף�����ô�ܵ��������ˣ�");
		if (! stringp(me->query("born")))
		{
			message_vision("$N�������������˳�ȥ��\n", me);
			me->delete("born");
			me->move("/d/register/yanluodian");
			message_vision("ž��һ����$N���ӵ��˵��ϡ�\n", me);
			return;
		}

		message_vision("$N�������������˳�ȥ��\b", me);
		me->move(VOID_OB);
		message_vision("ž��һ����$N���ӵ��˵��ϡ�\n", me);
		return;
	}

	command("look " + me->query("id"));
}
