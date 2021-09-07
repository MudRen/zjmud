//laoren.c

inherit NPC;

void create()
{
	set_name("˵������", ({"shuoshu laoren", "laoren"}) );
	set("gender", "����" );
	set("age", 53);
	set("long","һλ��ü��Ŀ�����ˣ�����˵�顣\n");
	set("combat_exp", 6000);
	set("str", 30);
	set("attitude","heroism");

	setup();
	carry_object(__DIR__"obj/changpao")->wear();
	add_money("silver", 10);
}

void init()
{
	remove_call_out ("says");
	call_out("says", random(3), this_object());
}

void says(object me)
{
	string *msgs = ({
		"$N������ɫ��˵���顣\n",
		"$N���ϲ�����˵���顣\n",
		"$N˵��ü��ɫ�衣\n",
		"$N˵��������֪������Σ������»طֽ⡣��\n",
		"$N���������˼��ڲ�ˮ���ֿ�ʼ����˵�顣\n",
	});
	message_vision (msgs[random(sizeof(msgs))], me);
	remove_call_out("says");
	call_out("says",random(40),me);
}
