//inventory.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int i,j,all,page;
	object *inv, bao,ob;
	mapping count;
	mapping equiped;
	mapping unit;
	mapping ids;
	mapping itype;
	string *text,pops,short_name;
	
	string str,sss;
	string *dk=({});

	if( !arg )
	{
		page = 1;
	}
	else if(sscanf(arg,"%d %s",page,arg)!=2)
	{
		page = 1;
	}

	if (wizardp(me) && arg)
	{
		ob = find_player(arg);
		if (! ob) ob = find_living(arg);
		if (! ob) ob = present(arg, environment(me));
		if (! ob) return notify_fail("û�������ҡ�\n");
	}

	if (! ob) ob = me;

	inv = all_inventory(ob);
	if (! sizeof(inv))
	{
		write(ZJOBLONG+((ob == me) ? "�㹲��"HIY+ob->query("yuanbao")+"Ԫ��"NOR"��Ŀǰ������û���κζ�����\n" : ob->query("yuanbao")+"����û��Я���κζ�����\n"));
		return 1;
	}
	for (i = 0; i < sizeof(inv); i++)
	{
		short_name = inv[i]->query("name");
//		short_name = inv[i]->query("name")+ZJBR+inv[i]->query("id");
		if(inv[i]->query_amount())
			short_name = inv[i]->query_amount() + inv[i]->query("base_unit") + short_name;

		sss = short_name;
		if (inv[i]->query("equipped"))
			sss = HIG"��"NOR+sss;
		else sss = " "+sss;

		dk += ({ sss + ":look " + file_name(inv[i]) });
	}
	text = sort_array(dk, 1);

	str = ZJOBLONG+sprintf("%s����"HIY"%dԪ����"NOR+ZJBR"���ϴ���������Щ����(%d�������� %d%%)��\n",
		      (ob == me)? "��" : ob->name(),ob->query("yuanbao"),sizeof(text),
		      (int)ob->query_encumbrance() * 100 / (int)ob->query_max_encumbrance());

	str += ZJOBACTS2+ZJMENUF(2,2,9,30);

	all = sizeof(text)/20;
	if(sizeof(text)%20) all += 1;
	if(page<1) page = 1;
	if(page>all) page = all;
	j = (page-1)*20;
	i = page*20;
	if (i >= sizeof(text)) i = sizeof(text);
	i--;
	if(all>1)
		str += "��һҳ:inventory "+(page-1)+" "+ob->query("id")+ZJSEP"��һҳ:inventory "+(page+1)+" "+ob->query("id")+ZJSEP;
	str += implode(text[j..i], ZJSEP);
	write(str+"\n");
	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: inventory
 
���г���(��)Ŀǰ������Я����������Ʒ��
 
ע : ��ָ����� " i " ���档

HELP );
	return 1;
}