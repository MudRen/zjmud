// new_sowrd.c

#include <weapon.h>
inherit BLADE;

void create()
{
	set_name(HIG "���嵶" NOR, ({ "new blade"}));
	set_weight(6000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("icon","05035");
		set("long", "����һ�������Ƴɵ�"+this_object()->query("name")+"���Ƕ���ʹ���ر�Ϊ���ֶ�����!\n");
		set("value", 10);
		set("material", "steel");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
	  //---------------------------------------------------------------
	      //��װ����
		set("suit",HIG"�¶���װ"NOR);  //��װ����
		set("suit_lvl",1);	     //��װ�ȼ�
		set("suit_count",4);	   //��װ��������
	      //��װ������
		set("suit_mod/cloth","�¶�����");
		set("suit_mod/boots","�¶���ѥ");
		set("suit_mod/pants","�¶�����");
		set("suit_mod/sword","�¶���");
		set("suit_mod/blade","�¶���");
		set("suit_mod/hands","�¶�����");
	       //��װȫ�������츳Ч��  
		set("suit_eff/strength",1);      //����
		set("suit_eff/intelligence",1);      //����  
		set("suit_eff/spirituality",1);      //    һ��
		set("suit_eff/constitution",1);      //����  
		//��װȫ�����Ӽ���Ч��     
	       set("suit_eff_skill/dodge",10);   
	       set("suit_eff_skill/sword",10);
	       set("suit_eff_skill/blade",10);
	       set("suit_eff_skill/cuff",10);
	       set("suit_eff_skill/strike",10);
	       set("suit_eff_skill/finger",10);
	       set("suit_eff_skill/claw",10);
       //------------------------------------------------------
	}
	init_blade(35);
	setup();
}
int query_autoload()
{
	return 1;
}