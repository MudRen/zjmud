// qiuhang.c �� 

#include <ansi.h>

inherit NPC;
inherit F_DEALER;
string ye_wu() ;
void create()
{
	set_name("��", ({ "qiu hang", "qiu" }));
	set("title", "�����ϰ�");
	set("nickname", "�ϻ�ͷ");
	set("shen_type", 0);
	set("dealer", "pawn");
	set("gender", "����");
	set_max_encumbrance(100000000);
	set("age", 55);
	set("str", 100);
	set("long", "һ���ϼ��̣���Ҫ�����ˣ�\n");
	set("no_get_from", 1); 
	 set("inquiry", ([
			 "��ҵ���" : (: ye_wu :),		     
	]));
	set_skill("unarmed", 60);
	set_skill("dodge", 60);
	set_temp("apply/attack", 30);
	set_temp("apply/attack", 30);
	set_temp("apply/damage", 15);

	set("combat_exp", 50000);
	set("attitude", "friendly");
	
	setup();
	carry_object("/clone/misc/cloth")->wear();
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
void unconcious()
{
	die();
}
void die()
{
	message_vision("\n$N���ˡ�\n", this_object());
	destruct(this_object());
}
