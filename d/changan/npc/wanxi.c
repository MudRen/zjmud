//wanxi.c

inherit NPC;
inherit F_DEALER;
string ye_wu() ;
void create()
{
	set_name("����ϲ", ({ "xiao wanxi", "xiao", "wanxi"}));
	set("title", "�����ϰ�");
	set("shen_type", 1);
	set("gender", "����");
	set_max_encumbrance(100000000);
	set("age", 34);
	set("str", 100);
       set("dealer", "pawn");
	set("long",
		"����ϲ�Ƕ�����Ա��İ��ܡ�\n");
	set("no_get_from", 1);
	set_skill("unarmed", 60);
	set_skill("dodge", 60);
	set_temp("apply/attack", 30);
	set_temp("apply/attack", 30);
	set_temp("apply/damage", 15);
	set("combat_exp", 50000);
	set("attitude", "friendly");
	set("inquiry", ([
			 "��ҵ���" : (: ye_wu :),		     
	]));
	setup();
	carry_object(__DIR__"obj/choupao")->wear();
}

void init()
{
	 add_action("do_list", "list");
	add_action("do_buy", "buy");
	add_action("do_sell", "sell");
	add_action("do_value", "value");
	add_action("do_pawn", "pawn");
	add_action("do_check", "listp");
	add_action("do_redeem", "redeem");
}
//ҵ��list
string ye_wu()
{
   write(""WHT"�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m"NOR"\n");
   write( HIY"  �� ���� ��: "+NOR+HIG"( value ��Ʒ )    ��������Ʒ��ֵ��      \n"+NOR);
   write( HIY"  �� �䵱 ��: "+NOR+HIG"( pawn ��Ʒ )     ���䵱��Ʒ��      \n"+NOR);
   write( HIY"  �� ��ѯ ��: "+NOR+HIG"( listp ��Ʒ )    ����ѯ�䵱��Ʒ��      \n"+NOR);
   write( HIY"  �� ��� ��: "+NOR+HIG"( redeem ��Ʒ )   ����ص䵱����Ʒ��  \n"+NOR);
   write( HIY"  �� ���� ��: "+NOR+HIG"( sell ��Ʒ )     �����ϸ����̡�\n"+NOR);
   write( HIY"  �� �б� ��: "+NOR+HIG"( list )	  ���鿴������Ʒ��\n"+NOR);
   write(""WHT"�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i"NOR"\n");
   return HIR"�͹���ʲô�Ը�������"+NOR;
}
int clean_up()
{
	return 0;
}

void die()
{
	message_vision("\n$Nһ���ҽУ����ˡ�\n", this_object());
	destruct(this_object());
}

void unconcious()
{
	die();
}
