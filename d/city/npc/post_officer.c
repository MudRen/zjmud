// post_officer.c 

inherit NPC;
string send_mail();
string receive_mail();
string give_quest();
void create()
{
	set_name("�ſ�", ({ "post officer", "post","officer" }) );
	set("title", "�䳤");
	set("gender", "����" );
	set("age", 43);
	set("long",
		"�ſ���ѩͤ����䳤�Ѿ���ʮ�����ˣ���Ȼ�ڼ��м�����Ǩ��\n"
		"���ᣬ����������Ϊ�᲻���뿪�������ˣ����Ӧangelus�����룬\n"
		"��������love�������ﵱ��վվ����angelus�������Ǹм���\n");
	set("combat_exp", 800);
	 set("level", 9);
	 set("icon", "05015");
	set("attitude", "friendly");
	set("inquiry", ([
		"��վ" : "�ǰ�... ������������䣬��Ҫ������",
		"����" : (: send_mail :),
		"����" : (: receive_mail :),
	]) );
	set_skill("literate", 70);
	set_skill("dodge", 50);
	set_skill("unarmed", 40);
	setup();
	add_money("coin", 70);
}
string send_mail()
{
	object mbox;
	if( this_player()->query_temp("mbox_ob") )
		return "������仹�ڰɣ�������Ϳ��Լ����ˡ�\n";
	if( !environment()
	||      base_name(environment()) != query("startroom") )
		return "���Ǳ�Ǹ��������һ�µ���վ�����Ұɡ�\n";
	seteuid(getuid());
	mbox = new(MAILBOX_OB);
	mbox->move(this_player());
	return "Ŷ... Ҫ������������������䣬���ŵķ�����������˵����\n";
}
string receive_mail()
{
	object mbox;
	if( this_player()->query_temp("mbox_ob") )
		return "������仹�ڰɣ������е��Ŷ������档\n";
	if( !environment()
	||      base_name(environment()) != query("startroom") )
		return "���Ǳ�Ǹ��������һ�µ���վ�����Ұɡ�\n";
	seteuid(getuid());
	mbox = new(MAILBOX_OB);
	mbox->move(this_player());
	return "�ã���������....���ˣ�����������⣬�������ɣ���������ˡ�\n";
}
void init()
{
    if( !environment()  ||  base_name(environment()) != query("startroom") )
	    return;

}


