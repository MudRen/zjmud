// familyd.c �������е�������Ϣ

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// �������������10��
#define MAX_FAMILY_FAME	 1000000000

// ÿ�����������100������
#define MAX_HATRED_PERSON       100

// �����˳�����ʱ��ÿ���Ƴ����ٸ�
#define HATREDP_REMOVED	 10

mapping family_fame = ([
	"������"   : 10000000,
	"�䵱��"   : 8000000,
	"ؤ��"     : 7000000,
	"ȫ���"   : 5000000,
	"��ɽ��"   : 4500000,
	"���ϻ���" : 4000000,
	"Ľ������" : 4000000,
	"ѩɽ��"   : 3500000,
	"���չ�"   : 3500000,
	"������"   : 3000000,
	"�һ���"   : 2500000,
	"������"   : 2000000,
	"��Ĺ��"   : 1500000,
	"������"   : 1200000,
	"��ң��"   : 1000000,
	"Ѫ����"   : 800000,
	"��ɽ����" : 600000,
	"ŷ������" : 500000,
	"�������" : 400000,
]);

// ����ID��Ӧ����������
static mapping family_name = ([
	"shaolin"  : "������",
	"wudang"   : "�䵱��",
	"gaibang"  : "ؤ��",
	"quanzhen" : "ȫ���",
	"huashan"  : "��ɽ��",
	"duan"     : "���ϻ���",
	"murong"   : "Ľ������",
	"xueshan"  : "ѩɽ��",
	"lingjiu"  : "���չ�",
	"emei"     : "������",
	"taohua"   : "�һ���",
	"shenlong" : "������",
	"gumu"     : "��Ĺ��",
	"xingxiu"  : "������",
	"xiaoyao"  : "��ң��",
	"xuedao"   : "Ѫ����",
	"jianzong" : "��ɽ����",
	"ouyang"   : "ŷ������",
	"hu"       : "�������",
]);

mapping last_family_fame;

//������ϯ����
mapping family_leader;
//������ϯ���ӽ���
mapping family_leader_bouns;

//���
mapping lunjian_leader;
//�������
mapping lunjian_leader_bouns;

int last_check;

// ���ɶԳ��˳�޶ȵ�����
private int sort_hatred(string id1, string id2, mapping hatred);

void create()
{
	seteuid(getuid());
	restore();
	if(!mapp(family_leader))
		family_leader = ([]);
	if(!mapp(family_leader_bouns))
		family_leader_bouns = ([]);
	if(!mapp(lunjian_leader))
		lunjian_leader = ([]);
	if(!mapp(lunjian_leader_bouns))
		lunjian_leader_bouns = ([]);
	set_heart_beat(1800);
}

void remove()
{
	save();
}

public void mud_shutdown()
{
	save();
}

public void clear_lunjian()
{
	lunjian_leader = ([]);
	lunjian_leader_bouns = ([]);
}

// ������ά�����ɵ�ͨ����Ϣ
private void heart_beat()
{
	int t;
	int last;
	string *all_fam;
	string fam;
	object ow,ob;

	t = time();

	last = last_check;
	if(!last) last = 0;

	if ((t / 86400) != (last / 86400))
	{
		if(localtime(t)[6]==0)
		{
		// ÿ���գ���������¼
			lunjian_leader = ([]);
			lunjian_leader_bouns = ([]);
		}
		if(localtime(t)[6]==6)
		// ÿ�����������ϯ���Ӽ�¼
			family_leader = ([]);

		// ���������˱仯���������ɵ�������Ϣ
		all_fam = keys(family_fame) - ({ 0 });
		last_family_fame = family_fame;
		family_fame = ([ ]);

		foreach (fam in all_fam)
			family_fame[fam] = last_family_fame[fam];
	}
	last_check = t;

	// �������ɵ�������Ϣ
	save();
}

public set_family_leader(string fname, string id)
{
	family_leader[fname] = id;
	save();
}

public string query_family_leader(string fname)
{
	if(!fname || !mapp(family_leader) || undefinedp(family_leader[fname]))
		return "";
	return family_leader[fname];
}

public set_lunjian_leader(string fname, string id)
{
	lunjian_leader[fname] = id;
	save();
}

public string query_lunjian_leader(string fname)
{
	if(!fname || !mapp(lunjian_leader) || undefinedp(lunjian_leader[fname]))
		return "";
	return lunjian_leader[fname];
}

public string bouns_family_leader(string fname, object me)
{
	object ob;
	string msg;

	if(!me->query("family"))
		return "�������ɶ�û��Ϲ��ɶ���֣�\n";
	if(me->query("family/family_name")!=fname)
		return "���Ǳ�������ô��\n";
	if(!mapp(family_leader) || undefinedp(family_leader[fname]) || family_leader[fname]!=me->query("id"))
		return "�㲻�Ǳ�����ϯ���ӣ�������ȡ������\n";
	if(!undefinedp(family_leader_bouns[fname])&&family_leader_bouns[fname]/86400==time()/86400)
		return "���ŵ���ϯ���ӽ��������Ѿ����Ź��ˣ�\n";
	if(localtime(time())[6]==6&&localtime(time())[2]<6)
		return "������0:00-6:00֮�䲻����ȡ������\n";

	family_leader_bouns[fname] = time();
	me->add("balance",300000);
	msg = "��õ���30��Ҵ�����\n";
	me->add("potential",2000);
	msg += "��õ���2000��Ǳ�ܽ�����\n";
	ob = new("/clone/shizhe/dan_chongmai4");
	msg += "��õ���"+ob->short()+"�Ľ�����\n";
	ob->move(me);
	log_file("bouns_family_leader",sprintf("%s��%s(%s)��ȡ��%s��ϯ������\n",ctime(time()),me->query("name"),me->query("id"),fname));
	save();
	return msg;
}

public string bouns_lunjian_leader(object me)
{
	object ob,obj;
	string *s,title,msg;
	int t,i;

	if(localtime(time())[6]==0&&localtime(time())[2]<21)
		return "��һ���۽�������Ҫ��ʼ�ˣ��Ͻ�׼��׼���μӽ���Ļ�ɽ�۽��ɣ�\n";

	msg = "";
	s = keys(lunjian_leader);
	for(i=0;i<sizeof(s);i++)
	{
		if(lunjian_leader[s[i]]==me->query("id"))
		{
			title = s[i];
			break;
		}
	}
	if(!title)
		return "��û������ƺţ���ʲô������\n";

	if((t=lunjian_leader_bouns[title]))
		return msg+title+"�Ľ����Ѿ����Ź��ˣ�\n";

	lunjian_leader_bouns[title] = time();
	ob = new("/clone/shizhe/dan_jiuzhuan");
	if(title=="��˫") ob->set_amount(2);
	msg += "��õ���"+ob->short()+"��\n";
	ob->move(me);
	log_file("bouns_lunjian_leader",sprintf("%s��%s(%s)��ȡ��%s������\n",ctime(time()),me->query("name"),me->query("id"),title));
	save();
	return msg;
}

public string check_lunjian_leader(object me)
{
	string *s,title;
	int i;

	s = keys(lunjian_leader);
	for(i=0;i<sizeof(s);i++)
	{
		if(lunjian_leader[s[i]]==me->query("id"))
		{
			title = s[i];
			break;
		}
	}
	return title;
}

// ���������������������Ϊ�գ�����mapping���ͣ�������������
// �ɵ������������������� �򷵻ظ��������ڵ��Ǹ����ɵ���
// ����������������ɣ��򷵻ظ����ɵ�������
public mixed query_family_fame(mixed ob)
{
	string fname;

	if (stringp(ob))
		return family_fame[ob];

	if (objectp(ob))
	{
		if (stringp(fname = ob->query("family/family_name")))
			return family_fame[fname];
		else
			return 0;
	}

	return family_fame;
}

// ��ѯ���������������Ϣ
public mapping query_all_last_family_fame()
{
	if (! mapp(last_family_fame))
		// û���������Ϣ�����ؽ����
		return family_fame;

	// �������������������Ϣ
	return last_family_fame;
}

// ��ѯ���ɵĳ����Ϣ�������ob���������ɵ����֣�Ҳ��������
// �е����
public mapping query_family_hatred(mixed ob)
{
	mapping hatred;
	string fname;

	if (objectp(ob))
		fname = ob->query("family/family_name");
	else
	if (stringp(ob))
		fname = ob;
	else
		fname = 0;

	if (! stringp(fname) || ! mapp(hatred = query("hatred/" + fname)))
		return 0;

	return hatred;
}

// �仯���������������ob���������ɵ����֣�Ҳ���������е���
// �
public void add_family_fame(mixed ob, int n)
{
	int new_fame;
	string fname;

	if (objectp(ob))
		fname = ob->query("family/family_name");
	else
	if (stringp(ob))
		fname = ob;
	else
		fname = 0;

	if (! stringp(fname) || undefinedp(family_fame[fname]))
		return;

	// �����µ���������
	new_fame = family_fame[fname] + n;
	if (new_fame < 0) new_fame = 0;
	if (new_fame > MAX_FAMILY_FAME)
		new_fame = MAX_FAMILY_FAME;
	family_fame[fname] = new_fame;
}

// ���ɼ��ɱ
public void family_kill(object killer, object victim)
{
	int kexp;
	int vexp;
	string vfam;
	string kfam;
	string kid;
	int fame_delta;
	mapping hatred;
	mixed *d;

	// ֻ�����֮��ĳ�ɱ�ż�������
	if (! objectp(killer) || ! playerp(killer) ||
	    ! objectp(victim) || ! playerp(victim))
		return;

	// ��ʦ֮��ıȻ��ɲ�������
	if (wizardp(killer) || wizardp(victim))
		return;

	kexp = killer->query("combat_exp");
	vexp = victim->query("combat_exp");
	kfam = killer->query("family/family_name");
	vfam = victim->query("family/family_name");

	if (stringp(kfam) && kfam == vfam)
	{
		// ͬ�Ų�ɱ��
		return;
	}

	if (kexp < vexp * 3 && vexp >= 100000)
	{
		// ɱ�ֵľ��鲻��ԶԶ�Ĵ��ڶԷ������ұ�ɱ��
		// ����һ���ľ��飬�⽫�������������Ľ��͡�
		fame_delta = vexp + killer->query("score") * 2 +
			     killer->query("weiwang") * 10;
		fame_delta /= 1000;
	} else
		// ���־���̫�٣����ǲ��̫�󣬲�Ӱ������
		fame_delta = 0;

	// �鿴ɱ�����ڵ������Ƿ������ߣ������ޣ����ܹ�
	// ���������ı仯��
	if (stringp(kfam))
	{
		string path;

		path = "hatred/" + kfam + "/" + victim->query("id");
		d = query(path);
		if (arrayp(d) && sizeof(d) >= 2 && intp(d[1]))
		{
			// ������ߣ����ɻ�ö��������
			if (d[1] > 2000)
				CHANNEL_D->do_channel(this_object(), "rumor",
					"��˵" + killer->name(1) + "������" +
					victim->name(1) + "��Ϊ" +
					kfam + "�ֻ��˹�����");
			fame_delta += d[1] / 3;

			// �Դ��˵ĳ�޽���(���͵�Ҫ�����ӵ�Ҫ��)��
			// ������Կ�fame_delta ���޶ȹ�˾�Ĳ���
			d[1] -= fame_delta;
			if (d[1] <= 0)
				delete(path);
			else
				set(path, d);
		}
	}

	// �����������ɵ�����
	add_family_fame(killer,  fame_delta);
	add_family_fame(victim, -fame_delta);

	// ͳ�Ƹ�ɱ�ֶԱ��ŵĲк��̶�
	if (! stringp(vfam))
		return;

	// ��޳̶Ⱥ������ı仯������һ����������(K����)����
	// �ǳ�޳̶ȵ��������ı仯��
	vexp = vexp / 1000 + 1;
	if (vexp > 5000)
		vexp = (vexp - 5000) / 16 + 2000;
	else
	if (vexp > 1000)
		vexp = (vexp - 1000) / 4 + 1000;

	kid = killer->query("id");
	if (! mapp(hatred = query("hatred/" + vfam)))
	{
		set("hatred/" + vfam + "/" + kid,
		    ({ killer->name(), vexp }));
		return;
	}

	// ÿ����������¼���ɸ�����
	if (! undefinedp(d = hatred[kid]))
	{
		if (! arrayp(d) || sizeof(d) < 2 ||
		    ! intp(d[1]) || ! stringp(d[0]))
		{
			// ���ID�����ݳ��˹���
			d = 0;
		}
	} else
	if (sizeof(hatred) >= MAX_HATRED_PERSON)
	{
		string *ids;
		int i;

		// ����ȥ��һЩ�ˣ�Ϊʲô��ȥ��һ��������Ϊ
		// �˷�ֹ����Ƶ���Ľ��й��˲�����
		ids = sort_array(keys(hatred),
				 (: sort_hatred :), hatred);
		for (i = 0; i < sizeof(ids) && i < HATREDP_REMOVED; i++)
			map_delete(hatred, ids[i]);
	}

	if (! arrayp(d))
		d = ({ killer->name(1), vexp });
	else
	{
		d[0] = killer->name(1);
		d[1] += vexp;
	}

	// ��¼����˵���Ϣ
	hatred[kid] = d;
}

// ȥ���������ɶ�ĳ���˵ĳ����Ϣ
public void remove_hatred(string id)
{
	mapping all_hatred, hatred;
	string fam;

	if (! mapp(all_hatred = query("hatred")))
		// ���ڻ�û�г����Ϣ
		return;

	// �������е�����
	foreach (fam in keys(all_hatred))
	{
		if (mapp(hatred = all_hatred[fam]))
			// ȥ�������ɶ�ĳ�˵ĳ����Ϣ
			map_delete(hatred, id);

		if (! mapp(hatred) || ! sizeof(hatred))
			// ��������Ѿ�û�г����Ϣ
			map_delete(all_hatred, fam);
	}
}

// ��������
private int sort_hatred(string id1, string id2, mapping hatred)
{
	mixed *d1, *d2;

	if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
		return -1;

	if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
		return 1;

	return d1[1] - d2[1];
}

public string query_family_name(string fid)
{
	string fam;

	if (undefinedp(fam = family_name[fid]))
		fam = fid;
	return fam;
}

public mapping query_all_family_name()
{
	return family_name;
}

public string query_save_file() { return DATA_DIR "familyd"; }
