// jinlin.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("����", ({ "jinlin", "jin" }) );
	set("gender", "����" );
	set("age", 18);
	set("long", "����һλ����ͯ�ӣ���³����������ͯ��֮һ��\n");
	set("title", HIC "�Ϸ�����" NOR CYN "��" HIR "��" NOR);
	set("nickname", HIY "����ͯ��" NOR);
	set("attitude", "friendly");
	setup();
}

int accept_object(object who, object ob)
{
	command("say �߶�ȥ��������Ҫ���ҡ�");
	return 0;
}

int accept_ask()
{
	message_vision("$N������˵����ɶ������ʦ��ȥ�����ҡ�\n",
		       this_object());
	return 1;
}
