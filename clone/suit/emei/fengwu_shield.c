// fengwu_shield.c

#include <ansi.h>
#include <armor.h>

inherit SHIELD	;

string do_wear();

void create()
{
	set_name(HIM "�۷���֮��" NOR, ({"fengwu shield"}));
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����ʥ����[������װ]�Ķ���\n");
		set("material", "shield");    //����
		set("armor_prop/armor", 100);  //����
		set("armor_prop/warm", 1);   //��ů
		set("value", 10);	 //��ֵ
		set("wear_msg", (: do_wear :));  //װ����Ϣ
		set("icon","05086");  //ͼ��
       //---------------------------------------------------------------
	      //��װ����
		set("suit",HIM"������װ"NOR);  //��װ����
		set("suit_lvl",3);	     //��װ�ȼ�
		set("suit_count",1);	   //��װ��������
	      //��װ������
		set("suit_mod/sword","����ȹ��");
		set("suit_mod/boots","����ͷ��");
		set("suit_mod/arrmor","���跨��");
		set("suit_mod/neck","���軤��");
		set("suit_mod/shield","��������");
	    //��װȫ������Ч��  //����һ�����ǵڶ������ԣ�����
		set("suit_eff/dex",1);    
		set("suit_eff/con",2);  
		set("suit_eff/int",3);    
		set("suit_eff/str",4);    
	  //     
		set("suit_eff_skill/fly",10);   
		set("suit_eff_skill/taoism",10);	       
       //---------------------------------------------------------------
	}
	setup();
}

string do_wear()
{
	object me;
	string msg;
	int per;

	me = this_player();
	per = me->query("per");
	if (me->query("gender") == "Ů��")
	{
		if (per >= 30)
			msg = HIC "$N" HIC "���Ὣһ��$n" HIC "�������ϣ���̬����֮����\n";
		else if (per >= 25)
			msg = HIG "$N" HIG "��$n" HIG "չ�����������ϡ�\n";
		else if (per >= 20)
			msg = YEL "$N" YEL "��$n" YEL "�������ϣ����������ӡ�\n";
		else    msg = YEL "$N" YEL "ë��ë�ŵİ�$n" YEL "�������ϡ�\n";
	} else
	{
		if (per >= 30)
			msg = HIC "$N" HIC "����һ�ӣ���$n" HIC "�������ϣ���������֮����\n";
		else if (per >= 25)
			msg = HIG "$N" HIG "��$n" HIG "չ�����������ϡ�\n";
		else if (per >= 20)
			msg = YEL "$N" YEL "��$n" YEL "�������ϣ����˳��½ǣ����������ӡ�\n";
		else    msg = YEL "$N" YEL "ë��ë�ŵİ�$n" YEL "�������ϣ����������\n";
	}
	return msg;
}

int query_autoload()
{
	return 1;
}
