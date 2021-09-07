//feifei.c

inherit NPC;

void greeting(object);
void init();

void create()
{
	set_name("�ʷ�", ({ "fei fei","fei" }) );
	set("gender", "����" );
	set("age", 35);
	set("long", "һ����ͷ����ĳ�ʦ����ֻС�۾���ͣ��գ���š�\n");
	set("shen_type", -1);
	set("combat_exp", 10000);
	set("str", 20);
	set("dex", 22);
	set("con", 20);
	set("int", 21);
	set("attitude", "friendly");
	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 3);
}

void init()
{
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	object obn;
	if( !ob || environment(ob) != environment() ) return;
	if( check_family(ob, "ŷ������") )
	{
		say("�ʷ�Ц������˵������λ" + RANK_D->query_respect(ob) +
		    "�����˰ɣ����ò͡�\n");
	}
	else 
		say("�ʷ�С��һգ��Ц������˵������λ" + RANK_D->query_respect(ob) +
		    "����ӭ���ιۣ��ɲ�Ҫ͵��Ӵ��\n");
	return;
}

int accept_object(object who, object ob)
{
	object obn;

	if (! ob->id("mu chai"))
		return notify_fail("�ʷʲ�Ҫ���������\n");

	message_vision("$N�ӹ�$n�ݹ�����" + ob->name() +
		       "������Ц��Ц��\n", this_object(), who);
	if (random(3) == 1)
	{
		obn = new("/clone/money/silver");
		obn->set_amount(5);
		obn->move(who, 1);
		tell_object(who,"�Ҷ����������ӣ���Ҫ���ţ�\n");
	}
	else
	{
		obn = new("/clone/money/silver");
		obn->set_amount(3);
		obn->move(who, 1);
		tell_object(who,"�ٽ��������Ժ��һ����ô��ģ�\n");
	}
	destruct(ob);
	return -1;
}
