#include <ansi.h>

inherit NPC;

void create()
{
	set_name("ׯ�ʳ�", ({ "zhuang yuncheng", "zhuang","yuncheng" }) );
	set("gender", "����" );
	set("age", 40);
	set("int", 28);
	set("long",
		"���Ǹ�����ʫ�飬ȴ���޲���֮����������\n"
	     +"��༭����ʷ���ԡ�������֮�ٸ淢��ȫ�Ҵ��뾩�С�\n" );

	set("attitude", "peaceful");
	set_skill("literate", 100);
	set("noget", "ׯ�ʳ�̾�����Ҳ����ˣ����߰ɡ������ҵ����Ҽ����˰���\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		"\nׯ�ʳ�˵����ֻ���ҵ������ģ������м��˽�Ҷ��������\n"
		"˭�������Ĺ��εļһﾹȻ��ȥ�淢���ҡ���...\n",
		"\nׯ�ʳ�˵����˭Ҫ����֮��ץ��ׯ���ͺ��ˡ�\n",
		"ׯ�ʳ�ͻȻ˵��: ������������Ҫ�������ߴ��кô�����\n",
		"\nׯ�ʳ�̾�˿�����˵������֪�������鷿�����ܣ�ֻ��ϧ�ҳ���ȥ����\n",
		"ׯ�ʳ�˵����˭Ҫ�����ң���һ������֪���Ķ���������\n",
	}));
	set("inquiry", ([
		"��֮��" :  "�����͵�ׯ��ȥ�кô���",
	]) );
	setup();
	carry_object( __DIR__"obj/cloth")->wear();
}

void init()
{
	object ob; 
	int i;

	ob = this_player();
	if (! userp(ob)) return;
	if (interactive(ob) && !is_fighting())
		say("ׯ�ʳǹ���Ц�������������������ˣ�\n");

	i = ob->query("weiwang");
	if (i < 20)
	{
		i+= 10;
		ob->set("weiwang", i);
		tell_object(ob, HIC "��Ľ�����������ˣ�"NOR"\n");
	}
}
